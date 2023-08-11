# core - The Gramado kernel

## What is Gramado?

    Gramado (c) is a 64bit multithreaded operating system.

## This repository has the source code for:

* Gramado boot loader
* Gramado kernel

## Where is the boot loader?

All the boot support can be found in boot/ folder.

## Where is the core kernel program.

The kernel core program is called KERNEL.BIN. It is found in the kernel/ folder.

## Where are the kernel modules?

The kernel has only one ring0 loadable module. It uses a static address and the symbols are resolved at runtime. See: newm0 or newm1.


## Kernel features.

> * Paging.
> * Threads.
> * FAT16 file system.
> * ps/2 keyboard. 
> * ps/2 mouse works fine only on qemu.
> * Serial port. 
> * IDE PATA. 
> * Window Server. See: gramado/core/

## Userland features.

> * Unix-like commands running in the virtual console.
> * Some few clients connected to the window server via unix-sockets.

## Libraries.

> * unix-like library. (rtl)
> * Lib for the window server's clients. (libgws)

## Fred's compilation on Linux.
```
    Host machine: Ubuntu 20.04.3 LTS
    Linux 5.15.0-41-generic x86_64
    gcc (Ubuntu) 11.2.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
```

## How to Build?

> See the [Gramado OS build instructions](https://github.com/gramado/gramado/blob/master/docs/build.md)

## Testing

```
	$ make
	$ cd core
	$ ./run
	$ make qemu-test
```

The old versions were tested for a long period of time on my 
real machine. A Gigabyte/Intel Core 2 Duo/Chipset VIA.
Now i'm testing only on qemu and virtualbox.
Please, give us some feedback.

## Documentation

> See the [docs](https://github.com/gramado/gramado/tree/master/docs).

## Author

* **Fred Nora** - [frednora](https://twitter.com/frednora)

## Contributors

* **Fred Nora** - [frednora](https://facebook.com/frednora)

## License

Gramado is a Free and Open Source operating system.
The source code uses the BSD license.

## Quotes:
> X


