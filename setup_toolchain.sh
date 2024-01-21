#!/bin/bash

# Credits: https://wiki.osdev.org/GCC_Cross-Compiler

export PREFIX="$PWD/toolchain"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"
GCC_LINK="https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.xz"
BINUTILS_LINK="https://ftp.gnu.org/gnu/binutils/binutils-2.41.tar.xz"



SRCS=$(mktemp -d -p $PWD)

build_gcc() {
    cd $SRCS
    wget $GCC_LINK -O gcc.tar.xz
    tar xf gcc.tar.xz
    cd gcc-*
    
    ./configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers

    make all-gcc -j$(nproc)
    make all-target-libgcc -j$(nproc)
    
    make install-gcc
    make install-target-libgcc
}

build_binutils() {
    cd $SRCS
    wget $BINUTILS_LINK -O binutils.tar.xz
    tar xf binutils.tar.xz
    cd binutils-*
    
    ./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make -j$(nproc)
    make install
}

main() {
    # Setup prefix 
    rm -rf "$PREFIX"
    mkdir "$PREFIX"

    build_binutils
    build_gcc

    # Cleanup
    rm -rf "$SRCS"

}

main 

