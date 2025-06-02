# MikanOS

Self-Made Operating System by Mikan OS!!

## How to build BootLoader

1. `source edk2_setup.sh aoi`
2. `cd $HOME/edk2`
3. `build`

## How to build Kernel

1. `source $HOME/osbook/devenv/buildenv.sh`
2. `make`

## How to Run BootLoader and Kernel on QEMU

`$HOME/osbook/devenv/run_qemu.sh $HOME/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi /workspaces/mikanos/aoi/kernel/kernel.elf`