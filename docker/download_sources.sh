#!/bin/bash

GCC_LINK="https://mirrors.hopbox.net/gnu/gcc/gcc-15.1.0/gcc-15.1.0.tar.xz"
BINUTILS_LINK="https://sourceware.org/pub/binutils/releases/binutils-2.44.tar.xz"

mkdir -p /sources
cd /sources

wget $GCC_LINK -O gcc.tar.xz
tar xf gcc.tar.xz

wget $BINUTILS_LINK -O binutils.tar.xz
tar xf binutils.tar.xz
