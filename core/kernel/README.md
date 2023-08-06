# kernel - The kernel program.

The kernel program is a program called KERNEL.BIN. 

## Where is the headers used by the kernel?

All the headers used by the kernel program are in include/ folder.

## Where is the libc support build the kernel program?

The libc support for the kernel program is in the crt/ folder.

## Where is the entry point for the kernel program?

The kernel program starts at the function _kernel_begin in head_64.asm. See: ke/x86_64/startup/.

## Where is the support for processes and threads?

All the support for processes and threads are in the ke/ps/ folder.

## Where is the memory support?

All the memory suppport is found in mm/ folder.

## Where is the device drivers?

All the device drivers embedded inside the kernel program are found in the dev/ folder.

## Where is the file system support?

All the file system support is found in the fs/ folder.

## Where is the block device support?

It is in dev/blkdev/ folder.

## Where is the char device support?

It is in dev/chardev/ folder.

## Where is the network device support?

It is in dev/netdev/ folder.

## Where is the network support?

The network manager is found net/ folder and the device driver is in dev/netdev/.

## Where is the user support?

All the user support is found in the user/ folder. 

## Where is the systemcalls support?

There is a thing called System Call Interface - SCI. All the handlers for the systemcalls are in sci.c in zero/visitor/.




