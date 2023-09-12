
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
#include "gramado/jiffies.h"

// Setup input mode.
#include "dev/io_ctrl.h"


//
// + (3) Libc headers.
//

// crt: Libc support.
#include "public/ktypes.h"
#include "public/ktypes2.h"
#include "kstdarg.h"
#include "kerrno.h"
#include "kcdefs.h"
#include "kstddef.h"
#include "kobject.h"
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
#include "admin/config/superv/kpid.h"

//
// + (4) Memory management.
//

// Memory management.
#include "mm/x64gpa.h"
#include "mm/x64gva.h"
#include "mm/gentry.h"
#include "mm/mm.h"
#include "mm/memmap.h" 
#include "mm/intelmm.h"
#include "mm/mmblock.h"
#include "mm/x64mm.h"
#include "mm/mmglobal.h"  // Deve ficar mais acima.
#include "mm/heap.h"      // Heap pointer support.
#include "mm/aspace.h"    // Address Space, (data base account).
#include "mm/bank.h"      // Bank. database

// memory and libc
#include "runtime.h"

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

// fb device
#include "dev/display/color.h"
// display device support.
#include "dev/display/common/display.h"
// bootloader display device
#include "dev/display/bldisp/bldisp.h"
#include "dev/display/fonts.h"
#include "dev/display/ascii.h"
#include "dev/display/ws.h"
#include "dev/display/ws2.h"
#include "dev/display/bg.h"
#include "dev/display/graphics.h"
#include "dev/grinput.h"

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
#include "net/network.h"     //(network) Gerenciamento de rede.  
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
#include "ps/callback.h"
#include "ps/sched.h"
#include "ps/queue.h"
#include "ps/mk.h"
#include "ps/dispatch.h"
#include "ps/msg.h"
#include "ps/thread.h"
#include "ps/process.h"


// Precisa de todos os componentes de ke/
#include "ke/ke.h"

//
// + (10) User.
//

//
// user/
//

// SM - Security Manager.
// Autentication, security.
#include "user/security/usession.h"
#include "user/security/room.h"       // (window station)
#include "user/security/desktop.h"

// SM - Session Manager.
#include "user/session/logon.h"
#include "user/session/logoff.h"

// User
#include "user/user.h"
#include "user/security.h"


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

// ==============================
// #bugbug: O resto das coisas daqui pra 
// baixo são incluidas mais de uma vez, pois não te ifndef pra elas
// podemos colocar todas elas dentro de arquivos .h
// e mover as definições para arquivos .c.

// ------------------------------
// Product type.
typedef enum {
    PT_UNDEFINED,
    PT_THINGS,          // Things.
    PT_EDGEDEVICES,     // Edge Devices.
    //PT_COREDEVICES,   // Core Devices. (haha)
}ProductType_t;
//Type of product.
extern int g_product_type; 

// ------------------------------
// Platform type.
typedef enum {
   PFT_16BIT,       //16bit processor.
   PFT_32BIT,       //32bit processor.
   PFT_64BIT,       //64bit processor.
   //...
}PlatformType_t;
//size of processor word.
extern int g_platform_type;

// ------------------------------
// UP ou MP
typedef enum {
    SYSTEM_TYPE_NULL,
    SYSTEM_TYPE_UNIPROCESSOR,
    SYSTEM_TYPE_MULTIPROCESSOR
} SystemType_t;
extern int g_system_type;


extern unsigned int g_processor_count;
extern int g_smp_initialized;

//
// == current ======================================================
//

// GRAMADO_JAIL, GRAMADO_P1 ...
extern int current_mode;

#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...

// x86 ...
extern int current_arch;
// Organização de usuários.
extern int current_user; 
extern int current_group; 


// Organização dos processos

// ------
// see: process.c
// Process used by the console during the job control.
// #hackhack: 
// For now we are using the control thread associated with the
// window with focus.
// #todo
// But we need to use the control thread of the foreground process
// associated with the console TTY.
extern pid_t foreground_process;
// This is the process with the active thread.
extern pid_t active_process;    
// [Processing time]
// Only these can read the keyboard input.
// Sometime it's the terminal.
// It's child will read into a file.
// See: ps/process.c
extern pid_t criticalsection_pid;
// ------


// ------
// See: ps/thread.c
extern tid_t current_thread;     // Currently having the processing time.
extern tid_t foreground_thread;  // Input thread.
extern tid_t active_thread;      // This thread will receive the input.
extern tid_t next_thread;        // next user mode thread.
// ------

pid_t current_dead_process;
int current_dead_thread;


// Current runlevel. Used in init process.
extern int current_runlevel;

// Organização dos discos.
extern int current_disk;
extern int current_volume;

// Organização dos arquivos.
extern int current_directory;
extern int current_file;

// Organização dos terminais
extern int current_tty;
extern int current_terminal;
//extern int current_pty;
//extern int current_pts;


//se ele est'a inicializado ou nao
int dead_thread_collector_status;

// se 'e para usalo ou nao
int dead_thread_collector_flag;

//cr3. current page directoory address.
unsigned long current_process_pagedirectory_address;

// Logon
extern int g_logged;

// Drivers support
int g_driver_ps2keyboard_initialized;   //ps2 keyboard
int g_driver_ps2mouse_initialized;      //ps2 mouse

int g_driver_video_initialized;
int g_driver_apic_initialized;
int g_driver_hdd_initialized;

int g_driver_pci_initialized;
int g_driver_rtc_initialized;
int g_driver_timer_initialized;
//...

//internal modules support.
int g_module_shell_initialized;
int g_module_debug_initialized;
int g_module_disk_initialized;
int g_module_volume_initialized;
int g_module_fs_initialized;
int g_module_gui_initialized;
int g_module_logoff_initialized;
int g_module_logon_initialized;
int g_module_mm_initialized;
int g_module_objectmanager_initialized;
int g_module_runtime_initialized;
int g_module_uem_initialized;             //user environment manager.
//...


// Kernel information variables.
extern unsigned long KernelSize;
extern unsigned long KernelHeapSize;
extern unsigned long KernelStackSize;
extern unsigned long KernelPages;
//...

// symbol table
extern int g_kernel_symbols_available;


//#bugbug
//move this to kernel (ring 0) crt support.
//error support.
extern unsigned long errno;

//
// Plataform support.
//

//environment variables.
#define PLATFORM_PATH  "/Platform"
#define HARDWARE_PATH  "/Platform/Hardware"
#define FIRMWARE_PATH  "/Platform/Firmware"
#define SYSTEM_PATH    "/Platform/System"
//#define USERS_PATH     "/Platform/Users"
//...

struct node_d
{
    void *data;
    struct node_d *flink;
    struct node_d *blink;    
};

// Linked list support.
struct linkedlist_d
{
    struct node_d *head;
    struct node_d *tail;
};

// Save args support. 
struct kernel_args_d
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
}; 
struct kernel_args_d  KernelArgs;


//system classes.
struct system_classes_d
{
    //unsigned long Gramado; //@todo: Include this one.
    unsigned long Executive;
    unsigned long Microkernel;
    unsigned long Hal;
};
struct system_classes_d  SystemClasses;


//Kernel classes.
struct kernel_classes_d
{
    struct system_classes_d *System;
    //..
};
struct kernel_classes_d  KernelClasses;
//...

//
// == prototypes ==========================================
//


//
// Used during the kernel initialization.
//

// ::(1)
// The kernel starts at ke/x86_64/startup/
// see: '_kernel_begin' in head_64.asm.

// ::(2)
// Global initialization.
// see: init.c
void I_kmain(int arch_type);


// x86_64 Initialization. (Main routine)
// see: x64init.c
int I_x64main(void);

// ::(3)
// see: x64init.c
void I_x64ExecuteInitialProcess(void);

// ===========================

void gramado_shutdown (int how);

// Finalizations support.
void faults(unsigned long number);
void panic ( const char *format, ... );
void soft_die(void);
void die (void);
