
// kernel.h
// Created by Fred Nora.
// Gramado OS headers.

// Order:
//   + (1) Configuration of product and version.
//   + (2) Main supervisor configuration.
//   + (3) Libc headers.
//   + (4) Memory management.
//   + (5) HAL.
//   + (6) Devices.
//   + (7) Network.
//   + (8) File system.
//   + (9) Process structures.
//   + (10) User.
//   + (11) Kernel-mode callable interfaces.

//
// + (1) Configuration of product and version.
//

/*
Holy is the Lord revealed before my eyes
And my burning heart can scarcely take it in
As I behold Your beauty with unworthy eyes
The only song my soul can find to sing
Is hallelujah
Hallelujah
Hallelujah, my King - (Transfiguration)
*/

// Product and version.
// ==================================
#include "beauty/product.h"  // Product type
#include "beauty/version.h"  // Product version
#include "beauty/config.h"

// ==================================
#include "bootinfo.h"
#include "mode.h"
#include "state.h"
// ==================================
// utsname
// Structure describing the system and machine
#include "u.h"          // User
#include "utsname.h"
// ==================================
// system
#include "system.h"
// ==================================

//
// + (2) Main supervisor configuration.
//

// ==================================
// Supervisor:
// Kernel configuration.
// Compiling.
//#include "kconfig.h"
#include "klimits2.h"
#include "gdef.h"

#include "gdevice.h"
#include "ginput.h"  // input manager support.

#include "gspin.h"
#include "gwd.h"     // whatch dogs.
#include "pints.h"   // profiler

#include "kinit.h"   // kernel initialization.

// ===============================

#include "info.h"    // last one?
#include "request.h"
#include "debug.h"

// Gramado configuration.
#include "jiffies.h"

// Setup input mode.
#include "io_ctrl.h"


//
// + (3) Libc headers.
//

// crt: Libc support.
#include "ktypes.h"
#include "ktypes2.h"

#include "kobject.h"

// Legacy stuff.
#include "kstdarg.h"
#include "kerrno.h"
#include "kcdefs.h"
#include "kstddef.h"
#include "klimits.h"
#include "kstdio.h"
#include "kstdlib.h"
#include "kstring.h"
#include "kctype.h"
#include "kiso646.h"
#include "ksignal.h"
#include "kunistd.h"
#include "kfcntl.h"
#include "kioctl.h"
#include "kioctls.h"
#include "ktermios.h"
#include "kttydef.h"

// Globals. PIDs support.
#include "kpid.h"

//
// + (4) Memory management.
//

// Memory management.
#include "mmsize.h"
#include "x64/x64gpa.h"
#include "x64/x64gva.h"
#include "gentry.h"
#include "mm.h"
#include "memmap.h" 
#include "intelmm.h"
#include "mmblock.h"
#include "mmusage.h"
#include "x64/x64mm.h"
#include "mmft.h"
#include "mmglobal.h"  // Deve ficar mais acima.
#include "heap.h"      // Heap pointer support.
#include "aspace.h"    // Address Space, (data base account).
#include "bank.h"      // Bank. database

//
// + (5) HAL.
//

// hal
#include "ports64.h"
#include "cpu.h"
#include "x64/tss.h"
#include "x64/x64gdt.h"
#include "x64/x64.h"
#include "detect.h"
// hal pci
#include "pci.h"  // PCI bus.
// hv
#include "hv.h"
// hal cpu
#include "x64/cpuid.h"
#include "up.h"
#include "mp.h"
// hal pic/apic
#include "pic.h"
#include "apic.h"
#include "apictim.h"
#include "ioapic.h"
#include "breaker.h"
// hal timers.
#include "pit.h"
#include "rtc.h"
// hal io
#include "io.h"    //io.
// hal global
#include "hal.h"     // last one.

//
// + (6) Devices.
//

//  primeiro char, depois block, depois network.

//
// TTY ------------------
//


#include "ttyldisc.h"
#include "ttydrv.h"
#include "tty.h"
#include "pty.h"
#include "console.h"

//
// Serial devices ------------------
//

// hw stuff - display device
// display device support.
#include "display.h"
// bootloader display device
#include "bldisp.h"

// sw - Graphics Engine
#include "color.h"
#include "fonts.h"
#include "ascii.h"
#include "bg.h"

#include "msgcode.h"
#include "ws2.h"

#include "gre.h"
// caliuser
#include "ws.h"
#include "input.h"
#include "callback.h"

// Serial port. (COM).
#include "serial.h"

// ps2 - i8042
#include "vk.h"
#include "kbdabnt2.h"
#include "kbdmap.h"
#include "keyboard.h"
#include "ps2kbd.h"
#include "mouse.h"
#include "ps2mouse.h"
#include "i8042.h"
#include "ps2.h"

//
// Block devices ----------------------
//

// ata, sata
#include "ata.h"

// storage
#include "superblk.h"
#include "volume.h"
#include "disk.h"
#include "storage.h"

//
// + (7) Network.
//

//
// Network devices ---------------------------
// 

// primeiro controladoras depois protocolos
// e1000 - nic intel
#include "e1000.h"


// network
#include "net/mac.h"
#include "net/host.h"
#include "net/in.h"
#include "net/un.h"
// Protocols
#include "net/ethernet.h"
#include "net/arp.h"
#include "net/ip.h"
#include "net/tcp.h"
#include "net/udp.h"
#include "net/dhcp.h" 
#include "net/icmp.h" 
// Network
#include "net/nports.h"     //(network) Network Ports  (sw)
#include "net/inet.h"
#include "net/network.h"     //(network) Gerenciamento de rede.  
#include "net/socklib.h"     //
#include "net/socket.h"      //last always

// ----------------------

// Last:
// Device manager.
#include "devmgr.h"

//
// + (8) File system.
//

// ----------------------
// Depois de devices.

// fs
#include "path.h"      // path.
#include "fatlib.h"    // fat16 library.
#include "fat.h"       // fat16.
#include "inode.h"
#include "exec_elf.h"
#include "pipe.h"
#include "fs.h"


//
// + (9) Process structures.
//

//
// Kernel --------------------------
//

// ps
#include "prio.h"     // Priority
#include "quantum.h"  // Quantum
#include "image.h"
#include "x64/x64cont.h"
#include "ts.h"
#include "tasks.h"
#include "queue.h"
#include "mk.h"
#include "dispatch.h"
#include "msg.h"
#include "thread.h"
#include "process.h"
#include "sched.h"
#include "schedq.h"

// Precisa de todos os componentes de ke/
#include "ke.h"

//
// + (10) User.
//

//
// user/
//

#include "user.h"

#include "reboot.h"
#include "mod.h"

//
// + (11) Kernel-mode callable interfaces.
//

#include "zing.h"
#include "zz.h"
#include "layer.h"

// Syscalls. 
// (Called by the interrups 0x80, 0x81, 0x82, 0x83).
#include "syscalls.h"

// zero. (Used during the kernel initialization)
#include "zero.h"

// Maskable interrupts
#include "x64/x64mi.h"

#include "product.h"

// Project California
#include "cali.h"

