--------------------------------------
Product names:
    Gramado Kernel - core/
    Gramado DE     - userland/
--------------------------------------
    core/    - Boot loader, kernel and commands. 
    userland/ - Gramado Window System. (Window server and clients). (DE).
--------------------------------------
Build:
    Type 'make'
Clean up the mess:
    Go into the 'core/' directory and type 'make clean-all'
Running:
    Go into the core/ folder and type './run' or './runkvm'
--------------------------------------
Configuration file:
    include/config/superv/config.h
--------------------------------------
The boot loader starts at:
    core/boot/vd/fat/main.asm
--------------------------------------
The kernel starts at:
    kernel/arch/x86_64/startup/head_64.asm.
