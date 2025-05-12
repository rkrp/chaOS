#!/bin/bash

# Credits: https://wiki.osdev.org/GCC_Cross-Compiler

export PREFIX="$PWD/toolchain"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

SRCS=/sources

build_gcc() {
    cd $SRCS
    mkdir build-gcc
    cd build-gcc
    
    ../gcc-*/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c --without-headers

    make all-gcc -j$(nproc)
    make all-target-libgcc -j$(nproc)
    
    make install-gcc
    make install-target-libgcc
}

build_binutils() {
    cd $SRCS
    cd binutils-*
    
    ./configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make -j$(nproc)
    make install
}

build() {
    if [ "$1" == "gcc" ]; then
        build_gcc
    elif [ "$1" == "binutils" ]; then
        build_binutils
    else
        echo "Invalid argument. Use 'gcc' or 'binutils'."
        exit 1
    fi
}

build $1

