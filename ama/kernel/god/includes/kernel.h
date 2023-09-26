
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
#include "amazing/product.h"  // Product type
#include "amazing/version.h"  // Product version
#include "amazing/config.h"

// ==================================
#include "k4/bootinfo.h"
#include "k4/mode.h"
#include "k4/state.h"
// ==================================
// utsname
// Structure describing the system and machine
#include "k4/u.h"          // User
#include "k4/utsname.h"
// ==================================
// system
#include "k4/system.h"
// ==================================

//
// + (2) Main supervisor configuration.
//

// ==================================
// Supervisor:
// Kernel configuration.
// Compiling.
//#include "kconfig.h"
#include "k4/klimits.h"
#include "k4/gdef.h"

#include "k3/gdevice.h"
#include "k3/ginput.h"  // input manager support.

#include "k2/gspin.h"
#include "k2/gwd.h"     // whatch dogs.
#include "k2/pints.h"   // profiler

#include "k4/kinit.h"   // kernel initialization.

// ===============================

#include "k2/zcall/overall/info.h"    // last one?
#include "k2/zcall/overall/request.h"
#include "k2/zcall/overall/debug.h"

// Gramado configuration.
#include "k2/cali/jiffies.h"

// Setup input mode.
#include "k3/dev/io_ctrl.h"


//
// + (3) Libc headers.
//

// crt: Libc support.
#include "k2/public/ktypes.h"
#include "k2/public/ktypes2.h"

#include "k2/cali/kobject.h"

// Legacy stuff.
#include "k2/posix/kstdarg.h"
#include "k2/posix/kerrno.h"
#include "k2/posix/kcdefs.h"
#include "k2/posix/kstddef.h"
#include "k2/posix/klimits.h"
#include "k2/posix/kstdio.h"
#include "k2/posix/kstdlib.h"
#include "k2/posix/kstring.h"
#include "k2/posix/kctype.h"
#include "k2/posix/kiso646.h"
#include "k2/posix/ksignal.h"
#include "k2/posix/kunistd.h"
#include "k2/posix/kfcntl.h"
#include "k2/posix/kioctl.h"
#include "k2/posix/kioctls.h"
#include "k2/posix/ktermios.h"
#include "k2/posix/kttydef.h"

// Globals. PIDs support.
#include "k2/cali/kpid.h"

//
// + (4) Memory management.
//

// Memory management.
#include "k1/mm/mmsize.h"
#include "k1/mm/x64gpa.h"
#include "k1/mm/x64gva.h"
#include "k1/mm/gentry.h"
#include "k1/mm/mm.h"
#include "k1/mm/memmap.h" 
#include "k1/mm/intelmm.h"
#include "k1/mm/mmblock.h"
#include "k1/mm/mmusage.h"
#include "k1/mm/x64mm.h"
#include "k1/mm/mmft.h"
#include "k1/mm/mmglobal.h"  // Deve ficar mais acima.
#include "k1/mm/heap.h"      // Heap pointer support.
#include "k1/mm/aspace.h"    // Address Space, (data base account).
#include "k1/mm/bank.h"      // Bank. database

//
// + (5) HAL.
//

// hal
#include "k2/hal/ports64.h"
#include "k2/hal/cpu.h"
#include "k2/hal/tss.h"
#include "k2/hal/x64gdt.h"
#include "k2/hal/x64.h"
#include "k2/hal/detect.h"
// hal pci
#include "k2/hal/bus/pci.h"  // PCI bus.
// hv
#include "k2/hal/hv.h"
// hal cpu
#include "k2/hal/cpuid.h"
#include "k2/hal/up.h"
#include "k2/hal/mp.h"
// hal pic/apic
#include "k2/hal/pic.h"
#include "k2/hal/apic.h"
#include "k2/hal/breaker.h"
// hal timers.
#include "k2/hal/pit.h"
#include "k2/hal/rtc.h"
// hal io
#include "k2/hal/io.h"    //io.
// hal global
#include "k2/hal/hal.h"     // last one.

//
// + (6) Devices.
//

//  primeiro char, depois block, depois network.

//
// TTY ------------------
//


#include "k3/dev/tty/ttyldisc.h"
#include "k3/dev/tty/ttydrv.h"
#include "k3/dev/tty/tty.h"
#include "k3/dev/tty/pty.h"
#include "k3/dev/tty/console.h"

//
// Serial devices ------------------
//

// hw stuff - display device
// display device support.
#include "k3/dev/display/common/display.h"
// bootloader display device
#include "k3/dev/display/bldisp/bldisp.h"

// sw - Graphics Engine
#include "k2/ke/gre/color.h"
#include "k2/ke/gre/fonts.h"
#include "k2/ke/gre/ascii.h"
#include "k2/ke/gre/bg.h"
#include "k2/ke/gre/ws2.h"
#include "k2/ke/gre/gre.h"
// caliuser
#include "k2/ke/caliuser/ws.h"
#include "k2/ke/caliuser/input.h"
#include "k2/ke/caliuser/callback.h"

// Serial port. (COM).
#include "k3/dev/tty/serial.h"

// ps2 - i8042
#include "k3/dev/kbd/vk.h"
#include "k3/dev/kbd/kbdabnt2.h"
#include "k3/dev/kbd/kbdmap.h"
#include "k3/dev/kbd/keyboard.h"
#include "k3/dev/kbd/ps2kbd.h"
#include "k3/dev/mouse/mouse.h"
#include "k3/dev/mouse/ps2mouse.h"
#include "k3/dev/i8042.h"
#include "k3/dev/ps2.h"


//
// Block devices ----------------------
//

// ata, sata
#include "k3/dev/ata/ata.h"

// storage
#include "k3/dev/superblk.h"
#include "k3/dev/volume.h"
#include "k3/dev/disk.h"  
#include "k3/dev/storage.h" 

//
// + (7) Network.
//

//
// Network devices ---------------------------
// 

// primeiro controladoras depois protocolos
// e1000 - nic intel
#include "k3/dev/e1000/e1000.h"
// network
#include "k2/net/mac.h"
#include "k2/net/host.h"
#include "k2/net/in.h"
#include "k2/net/un.h"
// Protocols
#include "k2/net/prot/ethernet.h"
#include "k2/net/prot/arp.h"
#include "k2/net/prot/ip.h"
#include "k2/net/prot/tcp.h"
#include "k2/net/prot/udp.h"
#include "k2/net/prot/dhcp.h" 
#include "k2/net/prot/icmp.h" 
// Network
#include "k2/net/nports.h"     //(network) Network Ports  (sw)
#include "k2/net/inet.h"
#include "k2/net/network.h"     //(network) Gerenciamento de rede.  
#include "k2/net/socklib.h"     //
#include "k2/net/socket.h"      //last always

// ----------------------

// Last:
// Device manager.
#include "k3/dev/devmgr.h"  

//
// + (8) File system.
//

// ----------------------
// Depois de devices.

// fs
#include "k2/fs/path.h"      // path.
#include "k2/fs/fatlib.h"    // fat16 library.
#include "k2/fs/fat.h"       // fat16.
#include "k2/fs/inode.h"
#include "k2/fs/exec_elf.h"
#include "k2/fs/pipe.h"
#include "k2/fs/fs.h"


//
// + (9) Process structures.
//

//
// Kernel --------------------------
//

// ps
#include "k2/ps/prio.h"     // Priority
#include "k2/ps/quantum.h"  // Quantum
#include "k2/ps/image.h"
#include "k2/ps/x64cont.h"
#include "k2/ps/ts.h"
#include "k2/ps/tasks.h"
#include "k2/ps/queue.h"
#include "k2/ps/mk.h"
#include "k2/ps/dispatch.h"
#include "k2/ps/msg.h"
#include "k2/ps/thread.h"
#include "k2/ps/process.h"
#include "k2/ps/sched.h"
#include "k2/ps/schedq.h"

// Precisa de todos os componentes de ke/
#include "k2/ke/ke.h"

//
// + (10) User.
//

//
// user/
//

#include "k2/user/user.h"

#include "k2/zcall/overall/reboot.h"
#include "k2/zcall/overall/mod.h"

//
// + (11) Kernel-mode callable interfaces.
//

#include "k2/zcall/zing.h"
#include "k2/zcall/zz.h"
#include "k2/zcall/layer.h"

// syscalls. (Called by the interrups 0x80 and 0x82).
#include "k2/zcall/apis/sys/sci0.h"
#include "k2/zcall/apis/sys/sci1.h"
#include "k2/zcall/apis/sys/sci2.h"
#include "k2/zcall/apis/sys/syscalls.h"
// zero. (Used during the kernel initialization)
#include "k2/zcall/apis/zero/zero.h"
// newos. (Called by the interrups 0x80 and 0x82).
#include "k2/zcall/apis/newos/newos.h"

// Maskable interrupts
#include "k2/ps/x64mi.h"

#include "k2/cali/product.h"

// Project California
#include "k2/cali/cali.h"

