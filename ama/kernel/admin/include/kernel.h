
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

// Product and version.
// ==================================
#include "admin/product/product.h"  // Product type
#include "admin/product/version.h"  // Product version
// ==================================
#include "admin/bootinfo.h"
#include "admin/mode.h"
#include "admin/state.h"
// ==================================
// Gramado Configuration
#include "admin/config/gramado/config.h"
// ==================================
// utsname
// Structure describing the system and machine
#include "admin/config/gramado/u.h"          // User
#include "admin/config/gramado/utsname.h"
// ==================================
// system
#include "admin/config/gramado/system.h"
// ==================================


//
// + (2) Main supervisor configuration.
//

// ==================================
// Supervisor:
// Kernel configuration.
// Compiling.
#include "admin/config/superv/config.h"
#include "admin/config/superv/limits.h"
#include "admin/config/superv/limits2.h"
#include "admin/config/superv/gdef.h"
#include "admin/config/superv/gdevice.h"
#include "admin/config/superv/ginput.h"  // input manager support.
#include "admin/config/superv/gspin.h"
#include "admin/config/superv/gwd.h"     // whatch dogs.
#include "admin/config/superv/pints.h"   // profiler
//#include "admin/config/superv/info.h"    // last one?
#include "admin/config/superv/kinit.h"   // kernel initialization.

// ===============================

#include "zcall/overall/info.h"    // last one?
#include "zcall/overall/request.h"
#include "zcall/overall/debug.h"

// Gramado configuration.
#include "cali/jiffies.h"

// Setup input mode.
#include "dev/io_ctrl.h"


//
// + (3) Libc headers.
//

// crt: Libc support.
#include "public/ktypes.h"
#include "public/ktypes2.h"

#include "cali/kobject.h"

// Legacy stuff.
#include "posix/kstdarg.h"
#include "posix/kerrno.h"
#include "posix/kcdefs.h"
#include "posix/kstddef.h"
#include "posix/klimits.h"
#include "posix/kstdio.h"
#include "posix/kstdlib.h"
#include "posix/kstring.h"
#include "posix/kctype.h"
#include "posix/kiso646.h"
#include "posix/ksignal.h"
#include "posix/kunistd.h"
#include "posix/kfcntl.h"
#include "posix/kioctl.h"
#include "posix/kioctls.h"
#include "posix/ktermios.h"
#include "posix/kttydef.h"

// Globals. PIDs support.
#include "cali/kpid.h"

//
// + (4) Memory management.
//

// Memory management.
#include "mm/mmsize.h"
#include "mm/x64gpa.h"
#include "mm/x64gva.h"
#include "mm/gentry.h"
#include "mm/mm.h"
#include "mm/memmap.h" 
#include "mm/intelmm.h"
#include "mm/mmblock.h"
#include "mm/mmusage.h"
#include "mm/x64mm.h"
#include "mm/mmft.h"
#include "mm/mmglobal.h"  // Deve ficar mais acima.
#include "mm/heap.h"      // Heap pointer support.
#include "mm/aspace.h"    // Address Space, (data base account).
#include "mm/bank.h"      // Bank. database

//
// + (5) HAL.
//

// hal
#include "hal/ports64.h"
#include "hal/cpu.h"
#include "hal/tss.h"
#include "hal/x64gdt.h"
#include "hal/x64.h"
#include "hal/detect.h"
// hal pci
#include "hal/bus/pci.h"  // PCI bus.
// hv
#include "admin/config/hyperv/hv.h"
// hal cpu
#include "hal/cpuid.h"
#include "hal/up.h"
#include "hal/mp.h"
// hal pic/apic
#include "hal/pic.h"
#include "hal/apic.h"
#include "hal/breaker.h"
// hal timers.
#include "hal/pit.h"
#include "hal/rtc.h"
// hal io
#include "hal/io.h"    //io.
// hal global
#include "hal/hal.h"     // last one.


//
// + (6) Devices.
//

//  primeiro char, depois block, depois network.

//
// TTY ------------------
//


#include "dev/tty/ttyldisc.h"
#include "dev/tty/ttydrv.h"
#include "dev/tty/tty.h"
#include "dev/tty/pty.h"
#include "dev/tty/console.h"

//
// Serial devices ------------------
//

// hw stuff - display device
// display device support.
#include "dev/display/common/display.h"
// bootloader display device
#include "dev/display/bldisp/bldisp.h"

// sw - Graphics Engine
#include "ke/gre/color.h"
#include "ke/gre/fonts.h"
#include "ke/gre/ascii.h"
#include "ke/gre/bg.h"
#include "ke/gre/ws2.h"
#include "ke/gre/gre.h"

// caliuser
#include "ke/caliuser/ws.h"
#include "ke/caliuser/input.h"
#include "ke/caliuser/callback.h"

// Serial port. (COM).
#include "dev/tty/serial.h"

// ps2 - i8042
#include "dev/kbd/vk.h"
#include "dev/kbd/kbdabnt2.h"
#include "dev/kbd/kbdmap.h"
#include "dev/kbd/keyboard.h"
#include "dev/kbd/ps2kbd.h"
#include "dev/mouse/mouse.h"
#include "dev/mouse/ps2mouse.h"
#include "dev/i8042.h"
#include "dev/ps2.h"


//
// Block devices ----------------------
//

// ata, sata
#include "dev/ata/ata.h"

// storage
#include "dev/superblk.h"
#include "dev/volume.h"
#include "dev/disk.h"  
#include "dev/storage.h" 

//
// + (7) Network.
//

//
// Network devices ---------------------------
// 

// primeiro controladoras depois protocolos
// e1000 - nic intel
#include "dev/e1000/e1000.h"
#include "net/mac.h"
#include "net/host.h"
#include "net/in.h"
#include "net/un.h"

// Protocols
#include "net/prot/ethernet.h"
#include "net/prot/arp.h"
#include "net/prot/ip.h"
#include "net/prot/tcp.h"
#include "net/prot/udp.h"
#include "net/prot/dhcp.h" 
#include "net/prot/icmp.h" 

#include "net/nports.h"     //(network) Network Ports  (sw)
#include "net/inet.h"
#include "net/network.h"     //(network) Gerenciamento de rede.  
#include "net/socklib.h"     //
#include "net/socket.h"      //last always

// ----------------------

// Last:
// Device manager.
#include "dev/devmgr.h"  

//
// + (8) File system.
//

// ----------------------
// Depois de devices.

// fs
#include "fs/path.h"      // path.
#include "fs/fatlib.h"    // fat16 library.
#include "fs/fat.h"       // fat16.
#include "fs/inode.h"
#include "fs/exec_elf.h"
#include "fs/pipe.h"
#include "fs/fs.h"


//
// + (9) Process structures.
//

//
// Kernel --------------------------
//

// ps
#include "ps/prio.h"     // Priority
#include "ps/quantum.h"  // Quantum
#include "ps/image.h"
#include "ps/x64cont.h"
#include "ps/ts.h"
#include "ps/tasks.h"
#include "ps/queue.h"
#include "ps/mk.h"
#include "ps/dispatch.h"
#include "ps/msg.h"
#include "ps/thread.h"
#include "ps/process.h"

#include "ps/sched.h"
#include "ps/schedq.h"

// Precisa de todos os componentes de ke/
#include "ke/ke.h"

//
// + (10) User.
//

//
// user/
//

#include "user/user.h"

#include "zcall/overall/reboot.h"
#include "zcall/overall/mod.h"


//
// + (11) Kernel-mode callable interfaces.
//

#include "zcall/zing.h"
#include "zcall/zz.h"
#include "zcall/layer.h"

// syscalls. (Called by the interrups 0x80 and 0x82).
#include "zcall/apis/sys/sci0.h"
#include "zcall/apis/sys/sci1.h"
#include "zcall/apis/sys/sci2.h"
#include "zcall/apis/sys/syscalls.h"
// zero. (Used during the kernel initialization)
#include "zcall/apis/zero/zero.h"
// newos. (Called by the interrups 0x80 and 0x82).
#include "zcall/apis/newos/newos.h"

// Maskable interrupts
#include "ps/x64mi.h"

#include "cali/product.h"

// Project California
#include "cali/cali.h"


