FROM ubuntu:24.04

RUN apt-get update
RUN apt-get install -y \
    wget \
    xz-utils \
    build-essential \
    bison \
    flex \
    texinfo \
    libgmp-dev \
    libmpfr-dev \
    libmpc-dev \
    libisl-dev \
    git \
    curl \
    xorriso 

COPY download_sources.sh /
COPY setup_toolchain.sh /

# Download sources
RUN /download_sources.sh

RUN rm -rf /toolchain && mkdir /toolchain

# Build toolchain
RUN /setup_toolchain.sh binutils
RUN /setup_toolchain.sh gcc

ENV PATH="/toolchain/bin:$PATH"
WORKDIR /chaos


