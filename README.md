# chaOS
A minimal kernel for x86_64.

# Build
One needs to setup cross compilation toolchain first. Run the following in the root of the repo 
to setup cross-compiler toolchain. This should take a few minutes to setup but it is a single
time thing.  

## Build toolchain

    cd $CHAOS_SRC/docker/
    podman build -t chaos_build .

## Build ChaOS

    podman run -v $CHAOS_SRC:/chaos --security-opt label:disable chaos_build make

This will create `chaOS.iso` which is a bootable ISO image. 

# Running and debugging

Running the following will run it in qemu with debug enabled

    make run-uefi

# Credits
Thanks to [limine barebones](https://wiki.osdev.org/Limine_Bare_Bones) for the starting point. 

Thanks to osdev wiki and forums for all the learning resources. 
