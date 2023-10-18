
// kernel.h
// Created by Fred Nora.
// Gramado OS headers.


// Order:
// configuration, libc, devices ...

//
// Configuration of product and version.
//


// ==================================
// beauty/
// Product and version.
#include "beauty/product.h"  // Product type
#include "beauty/version.h"  // Product version
#include "beauty/config.h"

// ==================================
// ke/
#include "prefix/ke/bootinfo.h"
#include "prefix/ke/mode.h"
#include "prefix/ke/state.h"

// ==================================
// beauty/
// utsname
// Structure describing the system and machine
#include "beauty/u.h"          // User
#include "beauty/utsname.h"

// ==================================
// zcall/
// system
#include "prefix/zcall/system.h"


// ==================================
// ke/
// Supervisor:
// Kernel configuration.
// Compiling.
#include "prefix/ke/klimits2.h"
#include "prefix/ke/gdef.h"

// ==================================
// dev/
#include "prefix/dev/gdevice.h"
#include "prefix/dev/ginput.h"  // input manager support.

// ==================================
// ke/
#include "prefix/ke/gspin.h"
#include "prefix/ke/gwd.h"     // whatch dogs.
#include "prefix/ke/pints.h"   // profiler
#include "prefix/ke/kinit.h"   // kernel initialization.

// ===============================
// zcall/
#include "prefix/zcall/info.h"
#include "prefix/zcall/request.h"
#include "prefix/zcall/debug.h"

// ==================================
// ke/
// Gramado configuration.
#include "prefix/ke/jiffies.h"

// ==================================
// dev/
// Setup input mode.
#include "prefix/dev/io_ctrl.h"

// ==================================
// crt/
// Libc support.
#include "prefix/crt/ktypes.h"
#include "prefix/crt/ktypes2.h"
#include "prefix/crt/kobject.h"
// Legacy stuff.
#include "prefix/crt/kstdarg.h"
#include "prefix/crt/kerrno.h"
#include "prefix/crt/kcdefs.h"
#include "prefix/crt/kstddef.h"
#include "prefix/crt/klimits.h"
#include "prefix/crt/kstdio.h"
#include "prefix/crt/kstdlib.h"
#include "prefix/crt/kstring.h"
#include "prefix/crt/kctype.h"
#include "prefix/crt/kiso646.h"
#include "prefix/crt/ksignal.h"
#include "prefix/crt/kunistd.h"
#include "prefix/crt/kfcntl.h"
#include "prefix/crt/kioctl.h"
#include "prefix/crt/kioctls.h"
#include "prefix/crt/ktermios.h"
#include "prefix/crt/kttydef.h"

// ==================================
// ke/
// Globals. PIDs support.
#include "prefix/ke/kpid.h"

// ==================================
// mm/
// Memory management.
#include "prefix/mm/mmsize.h"
#include "prefix/mm/x64gpa.h"
#include "prefix/mm/x64gva.h"
#include "prefix/mm/gentry.h"
#include "prefix/mm/mm.h"
#include "prefix/mm/memmap.h" 
#include "prefix/mm/intelmm.h"
#include "prefix/mm/mmblock.h"
#include "prefix/mm/mmusage.h"
#include "prefix/mm/x64mm.h"
#include "prefix/mm/mmft.h"
#include "prefix/mm/mmglobal.h"  // Deve ficar mais acima.
#include "prefix/mm/heap.h"      // Heap pointer support.
#include "prefix/mm/aspace.h"    // Address Space, (data base account).
#include "prefix/mm/bank.h"      // Bank. database

// ==================================
// ke/
// hal
#include "prefix/ke/ports64.h"
#include "prefix/ke/cpu.h"
#include "prefix/ke/tss.h"
#include "prefix/ke/x64gdt.h"
#include "prefix/ke/x64.h"
#include "prefix/ke/detect.h"

// ==================================
// dev/
// PCI bus.
#include "prefix/dev/pci.h"

// ==================================
// ke/
// hv
#include "prefix/ke/hv.h"
// hal cpu
#include "prefix/ke/cpuid.h"
#include "prefix/ke/up.h"
#include "prefix/ke/mp.h"
// hal pic/apic/ioapic
#include "prefix/ke/pic.h"
#include "prefix/ke/apic.h"
#include "prefix/ke/apictim.h"
#include "prefix/ke/ioapic.h"
#include "prefix/ke/breaker.h"
// hal timers.
#include "prefix/ke/pit.h"
#include "prefix/ke/rtc.h"

// ==================================
// dev/
// io
#include "prefix/dev/io.h"

// ==================================
// ke/
// hal global
#include "prefix/ke/hal.h"


// ==================================
// dev/
// Devices
// primeiro char, depois block, depois network.
// tty
#include "prefix/dev/ttyldisc.h"
#include "prefix/dev/ttydrv.h"
#include "prefix/dev/tty.h"
#include "prefix/dev/pty.h"
#include "prefix/dev/console.h"
// hw stuff - display device
// display device support.
#include "prefix/dev/display.h"
// bootloader display device
#include "prefix/dev/bldisp.h"

// ==================================
// gramk/
// sw - Graphics Engine
#include "prefix/gramk/color.h"
#include "prefix/gramk/fonts.h"
#include "prefix/gramk/ascii.h"
#include "prefix/gramk/bg.h"

// ==================================
// ke/
#include "prefix/ke/msgcode.h"

// ==================================
// gramk/
#include "prefix/gramk/ws2.h"
#include "prefix/gramk/gre.h"
#include "prefix/gramk/ws.h"
#include "prefix/gramk/input.h"
#include "prefix/gramk/callback.h"

// ==================================
// dev/
// Serial port. (COM).
#include "prefix/dev/serial.h"
// ps2 - i8042
#include "prefix/dev/vk.h"
#include "prefix/dev/kbdabnt2.h"
#include "prefix/dev/kbdmap.h"
#include "prefix/dev/keyboard.h"
#include "prefix/dev/ps2kbd.h"
#include "prefix/dev/mouse.h"
#include "prefix/dev/ps2mouse.h"
#include "prefix/dev/i8042.h"
#include "prefix/dev/ps2.h"
// Block devices
// ata, sata
#include "prefix/dev/ata.h"
// storage
#include "prefix/dev/superblk.h"
// storage
#include "prefix/dev/volume.h"
#include "prefix/dev/disk.h"
// storage
#include "prefix/dev/storage.h"
// Network
// Network devices
// primeiro controladoras depois protocolos
// e1000 - nic intel
#include "prefix/dev/e1000.h"

// ==================================
// net/ 
// (network, protocols and socket)
// network
#include "prefix/net/mac.h"
#include "prefix/net/host.h"
#include "prefix/net/in.h"
#include "prefix/net/un.h"
// Protocols
#include "prefix/net/ethernet.h"
#include "prefix/net/arp.h"
#include "prefix/net/ip.h"
#include "prefix/net/tcp.h"
#include "prefix/net/udp.h"
#include "prefix/net/dhcp.h" 
#include "prefix/net/icmp.h" 
// Network
#include "prefix/net/nports.h"     //(network) Network Ports  (sw)
#include "prefix/net/inet.h"
#include "prefix/net/network.h"     //(network) Gerenciamento de rede.  
#include "prefix/net/socklib.h"     //
#include "prefix/net/socket.h"      //last always
// ----------------------
// Last:
// Device manager.
#include "prefix/dev/devmgr.h"

// ==================================
// fs/
// File system
// ----------------------
// Depois de devices.
// fs
#include "prefix/fs/path.h"      // path.
#include "prefix/fs/fatlib.h"    // fat16 library.
#include "prefix/fs/fat.h"       // fat16.
#include "prefix/fs/inode.h"
#include "prefix/fs/exec_elf.h"
#include "prefix/fs/pipe.h"
#include "prefix/fs/fs.h"

// ==================================
// ke/
// Process structures
// ps
#include "prefix/ke/prio.h"     // Priority
#include "prefix/ke/quantum.h"  // Quantum
#include "prefix/ke/image.h"
#include "prefix/ke/x64cont.h"
#include "prefix/ke/ts.h"
#include "prefix/ke/tasks.h"
#include "prefix/ke/queue.h"
#include "prefix/ke/mk.h"
#include "prefix/ke/dispatch.h"
#include "prefix/ke/msg.h"
#include "prefix/ke/thread.h"
#include "prefix/ke/process.h"
#include "prefix/ke/sched.h"
#include "prefix/ke/schedq.h"
// Precisa de todos os componentes de ke/
#include "prefix/ke/ke.h"

// ==================================
// zcall/
#include "prefix/zcall/user.h"

// ==================================
// ke/
#include "prefix/ke/reboot.h"

// ==================================
// zcall/
#include "prefix/zcall/mod.h"


// ==================================
// ke/
#include "prefix/ke/layer.h"

// ==================================
// zcall/
// Syscalls. 
// (Called by the interrups 0x80, 0x81, 0x82, 0x83).
#include "prefix/zcall/syscalls.h"
// zero. (Used during the kernel initialization)
#include "prefix/zcall/zero.h"

// ==================================
// ke/
// Maskable interrupts
#include "prefix/ke/x64mi.h"

// ==================================
// beauty/
#include "beauty/product2.h"

// ==================================
// zcall/
// Project California
#include "prefix/zcall/cali.h"


