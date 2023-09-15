
    Project: MOD1.BIN

    #hackhack
    For now the kernel needs to change the name of image he wants to load. 
    See the function I_x64CreateKernelProcess() in x64init.c.

    This is a loadable module for the kernel process. 
    It was compiled in a static address and was loaded by the kernel itself.
    The kernel is gonna dynamic link some symbols and call some functions in this program.

    The kernel is called KERNEL.BIN and this module is called MOD1.BIN.

    This module cannot use the rtl libc, it is because we don't wanna use syscalls in ring0. 
    So, this way, the module needs to link to the kernel.

    #todo
    Describe here how the initialization works, how the kernel can call the services here and 
    how this program can call the kernel services.
