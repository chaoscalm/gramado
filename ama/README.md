# ama - Bootloader and kernel.

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

## Kernel features. (see: ama/kernel/)

> * hw - cpu: Intel and AMD. 64bit only.
> * hw - mm: Paging. Chunck of 2MB, using 4KB pages.
> * hw - blk device: IDE PATA.
> * hw - char device: ps/2 keyboard. 
> * hw - char device: ps/2 mouse works fine only on qemu.
> * hw - char device: Serial port. (COM). Used for debug. 
> * hw - network device: e1000 Intel NIC. Works on Oracle virtual box.

> * sw - Processes: Process structure and Thread structure.
> * sw - Scheduler: Round robin. (Threads only).
> * sw - Syscalls using software interrups. (Traps).
> * sw - IPC: sockets.
> * sw - IPC: System messages using a queue in the thread structure. 
> * sw - tty: It has 4 ring 0 kernel virtual consoles in fullscreen raw mode. 
> * sw - tty: General use ttys and ptys for ring3 virtual terminals. 
> * sw - fs: FAT16 file system for boot partition. No system partition yet.
> * sw - posix libc: Ring0 implementation of libc functions called by the ring3 libraries.
> * sw - network: Small support for sockets.
> * sw - network: Small ring0 implementation of protocol stack. (ETHERNET, ARP, IP, UDP, TCP and DHCP).
> * sw - display: Bootloader display device. VESA.
> * sw - user: Very small implementation of user structure.
> * sw - APIs: See zcall/ folder.
> * sw - One loadable ring0 module, using static address.

## Userland features.

> * Display Server. See: userland/services/gramland/
> * Unix-like commands running in the virtual console.
> * Some few clients connected to the display server via unix-sockets.
> * Ring3 processes can access the i/o ports via syscall. (For ring3 drivers only).


## userland system programs.

> * zing/graminit/ - The init process.
> * zing/gramlan0/ - Gramland, the display server.
> * zing/netd/     - The network server.

## userland libraries, toolkits and apis.

> * posix libc - (rtl)
> * Client-sie library for GUI applications - (libgws)
> * see: zz/omega1/libs/ for all the libraries, toolkits and apis.

## userland user programs.

> * see: zz/omega2/apps/ for Client-side GUI application.
> * see: zz/omega2/commands/ for posix commands.
> * see: zz/omega2/drivers/ for ring3 drivers.
> * see: zz/omega2/servers/ for ring3 servers.

## userland system data.

> * zz/omega3/assets - Icons for the User Interface.
> * zz/omega3/base   - All binaries go here to build the final virtual disk.

## Fred's compilation on Linux.

```
    Host machine: Ubuntu 22.04.2 LTS
    Linux 5.15.0-83-generic x86_64
    gcc (Ubuntu) 11.4.0 
    GNU ld (GNU Binutils for Ubuntu) 2.38
    NASM version 2.15.05
```

## How to Build?

> See the [Gramado OS build instructions](https://github.com/gramado/gramado/blob/master/boring/docs/build.md)

## Testing

```
	$ make
	$ cd ama
	$ ./run
	$ make qemu-test
```

The old versions were tested for a long period of time on my 
real machine. A Gigabyte/Intel Core 2 Duo/Chipset VIA.
Now i'm testing only on qemu and virtualbox.
Please, give us some feedback.

## Documentation

> See the [docs](https://github.com/gramado/gramado/tree/master/boring/docs).

## Author

* **Fred Nora** - [frednora](https://twitter.com/frednora)

## Contributors

* **Fred Nora** - [frednora](https://facebook.com/frednora)

## License

Gramado is a Free and Open Source operating system.
The source code uses the BSD license.

## Quotes:
> X


