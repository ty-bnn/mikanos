# MikanOS

Self-Made Operating System by Mikan OS!!

## How to build BootLoader

1. `source edk2_setup.sh`
2. `cd $HOME/edk2`
3. `build`

## How to build Kernel

1. `clang++ -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++17 -c main.cpp`
2. `ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf main.o`

## How to Run BootLoader and Kernel on QEMU

`$HOME/osbook/devenv/run_qemu.sh $HOME/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi /workspaces/mikanos/aoi/kernel/kernel.elf`