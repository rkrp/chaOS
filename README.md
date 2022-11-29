# chaOS
A minimal kernel for x86_64.

# Build
One needs to setup cross compilation toolchain first. But it should work with gcc present in any 64-bit Linux distros. Run the following in the root of the repo. 

    make

This will give chaOS.iso which is a bootable ISO image. 

# Running and debugging

Running the following will run it in qemu with debug enabled

    make && make run-uefi

# Credits
Thanks to [limine barebones](https://wiki.osdev.org/Limine_Bare_Bones) for the starting point. 

Thanks to osdev wiki and forums for all the learning resources. 
