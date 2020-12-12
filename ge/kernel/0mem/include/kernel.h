/*
 * File: kernel.h
 * 
 *     This is the main header for the bse kernel.
 * 
 * History:
 *     2013 - Created by Fred Nora.
 *     2014~2018 - Resision.
 */

//
// == gramado modes =================================================
//

// See: 'current_mode'.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
// ...

//
// == input modes ==================================================
//

// See: 'current_input_mode'.


// ================
// fred:
// Talvez o bom mesmo seja usarmos apenas o input mode tty.
// Nesse caso para todos os tipos de aplicativo eles precisaram ler
// a tty para pegar o input no seu modo raw.
// Todo esse trabalho so existe porque o kernel esta construindo
// o evento de input ao inves de mandar o input no formato raw.
// ================


// Setup input mode.
// This is the mode used when we do not have a 
// loadble ring3 window server.
// Send the input event to the thread associated with the
// window with focus in the window server embedded inside the kernel.
#define INPUT_MODE_SETUP  1000

// tty input mode.
// In this mode we're gonna send the input to the tty buffer.
// This way a virtual terminal can share the input with its client.
#define INPUT_MODE_TTY    2000

// ...




//
// Externs.
//

//Stack for fome threads in kernel mode. 
extern unsigned long task0_stack;
extern unsigned long task1_stack;
extern unsigned long task2_stack;
extern unsigned long task3_stack;
extern unsigned long stack0_krn_ptr;
// ...


//#test 
//typedef int (*fn_ptr)();


// =========================================================


// oh boy
#include "gramado/0boy/0boy.h"

// config
#include "gramado/0config/version.h"    // Product. 
#include "gramado/0config/u.h"          // User
#include "gramado/0config/config.h"     // Compiling.

// globals
#include "gramado/0globals/limits.h"
#include "gramado/0globals/gpa.h"
#include "gramado/0globals/gva.h"
#include "gramado/0globals/gentry.h"
#include "gramado/0globals/gdef.h"
#include "gramado/0globals/gdevice.h"
#include "gramado/0globals/gobject.h"
#include "gramado/0globals/gspin.h"
#include "gramado/0globals/gwd.h"   //whatch dogs


// rtl 
// Inside the base kernel
#include "rtl/cdefs.h"
#include "rtl/stddef.h"
#include "rtl/types.h"
#include "rtl/types2.h"
#include "rtl/limits.h"
#include "rtl/kstdio.h"
#include "rtl/stdlib.h"
#include "rtl/string.h"
#include "rtl/ctype.h"
#include "rtl/iso646.h"
#include "rtl/signal.h"
#include "rtl/unistd.h"
#include "rtl/fcntl.h"
#include "rtl/ioctl.h"
#include "rtl/ioctls.h"
#include "rtl/termios.h"
#include "rtl/ttydef.h"



// memory management support.
#include "gramado/mm/mm.h"
#include "gramado/mm/memmap.h" 
#include "gramado/mm/intelmm.h"


// ws -
// #view presentation output.
#include "gramado/ws/view/display.h"
#include "gramado/ws/view/screen.h"
#include "gramado/ws/view/video.h"


// Render
#include "hal/render/r_render.h"


// #model. data model.
#include "gramado/ws/model/fonts.h"
#include "gramado/ws/model/ascii.h" 



// fs
#include "rtl/fs/path.h"         // path.
#include "rtl/fs/fat.h"          // fat16.
#include "rtl/fs/inode.h"
#include "rtl/fs/exec_elf.h"
#include "rtl/fs/pipe.h" 
#include "rtl/fs/fs.h"
#include "rtl/fs/vfs.h"


// ws - 
// view - input and presentation
#include "gramado/ws/view/prompt.h"

// view - showing the data.
#include "gramado/ws/view/bmp2.h"



// hal
#include "hal/portsx86.h"
#include "hal/halvid.h"
#include "hal/halmm.h"
#include "hal/cpu.h"
#include "hal/pte.h"
#include "hal/tss.h" 
#include "hal/cputypes.h"
#include "hal/x86pte.h"
#include "hal/x86.h"
#include "hal/x86iv.h"
#include "hal/x86gdt.h"
#include "hal/cpuamd.h"
#include "hal/detect.h"
#include "hal/serial.h"


//todo: podemos mover isso de lugar para perto de net/
#include "rtl/net/mac.h"



// hal/storage
#include "hal/storage/floppy.h"
#include "hal/storage/ata.h"
#include "hal/storage/super.h"
#include "hal/storage/volume.h"
#include "hal/storage/disk.h"  
#include "hal/storage/storage.h" 

// hal
#include "hal/pit.h"
#include "hal/pic.h"
#include "hal/apic.h"
#include "hal/cpuid.h"
#include "hal/rtc.h"



// ws - window server
// inputs
#include "gramado/ws/view/xproc.h"
#include "gramado/ws/view/keyboard.h"
#include "gramado/ws/view/mouse.h"
#include "gramado/ws/view/vk.h"
#include "gramado/ws/view/kbdabnt2.h"

// #view. drawing routines.
#include "gramado/ws/view/ldisc.h"


//storage (^)
#include "hal/storage/ide.h"


//pci
#include "hal/pci.h"


//storage (^)
#include "hal/storage/ahci.h"
#include "hal/storage/sata.h"


// hal (^)
#include "hal/usb.h"
#include "hal/up.h"
#include "hal/mp.h"
#include "hal/breaker.h"
#include "hal/hal.h"


// ps
#include "gramado/ps/x86cont.h"
#include "gramado/ps/ts.h"
#include "gramado/ps/tasks.h"
#include "gramado/ps/image.h"
#include "gramado/ps/clone.h"
#include "gramado/ps/process.h"
#include "gramado/ps/thread.h"
#include "gramado/ps/sched.h"
#include "gramado/ps/ipc.h"
#include "gramado/ps/ipccore.h"
#include "gramado/ps/sem.h"
#include "gramado/ps/queue.h"
#include "gramado/ps/realtime.h"
#include "gramado/ps/dispatch.h"
#include "gramado/ps/event.h"
#include "gramado/ps/ps.h"
#include "gramado/ps/mk.h"



// ws - 
// model business logic
#include "gramado/ws/model/kgwm.h"
#include "gramado/ws/model/ws.h"

// #view - designers
#include "gramado/ws/view/window.h"
#include "gramado/ws/view/menu.h"
#include "gramado/ws/view/pbar.h"
#include "gramado/ws/view/bmp.h"
#include "gramado/ws/view/line.h"

// #view. presentation
#include "gramado/ws/view/terminal.h"
#include "gramado/ws/view/guiconf.h"


//
// == Security ===============================
//

#include "gramado/security/usession.h"
#include "gramado/security/room.h"
#include "gramado/security/desktop.h"
#include "gramado/security/user.h"
#include "gramado/security/security.h"


// ws - window server, and beyond
#include "gramado/ws/logon.h"
#include "gramado/ws/logoff.h"

// model. business logic
#include "gramado/ws/model/kgws.h"


// tty
#include "rtl/tty/ttyldisc.h"
#include "rtl/tty/ttydrv.h"
#include "rtl/tty/tty.h"
#include "rtl/tty/pty.h"
#include "rtl/tty/vt.h"
#include "rtl/tty/console.h"


// =============================
// ws - i8042 ps2 controller.
#include "gramado/ws/view/i8042/i8042.h"
#include "gramado/ws/view/i8042/ps2mouse.h"
#include "gramado/ws/view/i8042/ps2kbd.h"
#include "gramado/ws/view/i8042/ps2.h"




//
//  ==== NETWORK ====
//

#include "rtl/net/connect.h" 
#include "rtl/net/host.h"
#include "rtl/net/ethernet.h"
#include "rtl/net/arp.h"
#include "rtl/net/udp.h"
#include "rtl/net/tcp.h"
#include "rtl/net/nicintel.h"    //intel nic - network interface controller.
#include "rtl/net/in.h"
#include "rtl/net/un.h"
#include "rtl/net/nports.h"     //(network) Network Ports  (sw)
#include "rtl/net/ip.h"         //(network) IP info.      (sw)
#include "rtl/net/ipv4.h" 
//#include "rtl/net/ipv6.h" 
#include "rtl/net/ipv4mac.h" 
#include "rtl/net/icmp.h" 
#include "rtl/net/packet.h"      // network packets.
#include "rtl/net/channel.h"     //(network) Channel       (sw)
#include "rtl/net/client.h"      //(network) Client process support. 
#include "rtl/net/ns.h"          //(network) Network Server.
#include "rtl/net/network.h"     //(network) Gerenciamento de rede.  
#include "rtl/net/socket.h"      //last always


//
// ==== DEVICES ====
//


// devices
#include "hal/devices.h"
#include "hal/devmgr.h"       
#include "hal/io.h"               //io.


#include "gramado/modules.h"     //module manager.
#include "gramado/debug.h"
#include "gramado/system.h"    //system manager.
#include "gramado/init.h"
#include "gramado/execve.h"  
// mm
#include "gramado/mm/mmglobal.h"  // Deve ficar mais acima.
#include "gramado/mm/heap.h"      // Heap pointer support.
#include "gramado/mm/aspace.h"    // Address Space, (data base account).

// storage 
#include "hal/dspace.h"    // Disk Space, (data base account). storage stuff

// mm
#include "gramado/mm/bank.h"      // Bank. database
#include "gramado/mm/x86mm.h"     // mm, memory manager support.



// ws - 
// view. input support.
#include "gramado/ws/view/cursor.h"


#include "gramado/messages.h"
#include "gramado/events.h"
#include "gramado/object.h"
#include "gramado/ss.h"


// profiler
#include "gramado/pints.h"


#include "rtl/runtime.h"


// kernel
#include "gramado/ke.h"
#include "gramado/ki.h"
#include "gramado/info.h"
#include "gramado/request.h"
#include "gramado/reboot.h"
#include "gramado/sub.h"       // gramado sub systems
#include "gramado/utsname.h"
#include "gramado/gpid.h"      // Globals. PIDs support.


// sci - system call interface
// All the functions in this folder can be called
// by the ring3 apps via system call.
// This is the last #include. :^)

#include "rtl/sci/syscall.h"        
#include "rtl/sci/sys.h"

// si - services interfce
#include "rtl/si/sifs.h"
#include "rtl/si/sins.h"
#include "rtl/si/siws.h"


// ==============================

//keyboard suppport 
//abnt2 flag.
//#todo: Move this to another file.
//maybe gdef.h
int abnt2;
//...


// Product type.
typedef enum {
   PT_THINGS,        // Things.
   PT_EDGEDEVICES,   // Edge Devices.
   //PT_COREDEVICES,   // Core Devices. (haha)
}ProductType_t;


//Type of product.
int g_product_type; 


// Platform type.
typedef enum {
   PFT_16BIT,       //16bit processor.
   PFT_32BIT,       //32bit processor.
   PFT_64BIT,       //64bit processor.
   //...
}PlatformType_t;


// UP ou MP
typedef enum {

    SYSTEM_TYPE_NULL,
    SYSTEM_TYPE_UNIPROCESSOR,
    SYSTEM_TYPE_MULTIPROCESSOR

} SystemType_t;




//
// == current ======================================================
//

// GRAMADO_JAIL, GRAMADO_P1 ...
int current_mode;

// INPUT_MODE_SETUP, INPUT_MODE_WS ...
int current_input_mode;

// x86 ...
int current_arch;


// Organização de usuários.
int current_user; 
int current_group; 



// Organização dos processos


// Process used by the console during the job control.
// #hackhack: 
// For now we are using the control thread associated with the
// window with focus.
// #todo
// But we need to use the control thread of the foreground process
// associated with the console TTY.
int foreground_process;


// [Processing time]
// Only these can read the keyboard input.
// Sometime it's the terminal.
// It's child will read into a file.
int current_process;   // Currently having the processing time.
int current_thread;    // Currently having the processing time.

int criticalsection_pid;

// [Focus]
int active_process;    // This is the process with the active thread.
int active_thread;     // This thread will receive the input.

//[Scheduler]
int next_thread;     //next user mode thread.


// Current runlevel. Used in init process.
int current_runlevel;


// Organização dos discos.
int current_disk;
int current_volume;

// Organização dos arquivos.
int current_directory;
int current_file;
int current_dead_process;
int current_dead_thread;

// Organização dos terminais
int current_tty;
int current_terminal;
//int current_pty;
//int current_pts;


//...

// ==== ====


//size of processor word.
int g_platform_type;






//se ele est'a inicializado ou nao
int dead_thread_collector_status;

// se 'e para usalo ou nao
int dead_thread_collector_flag;

//cr3. current page directoory address.
unsigned long current_process_pagedirectory_address;



//
// Logon.
//

int g_logged;


//
// GUI
//

//flag.
//If the kernel is in graphics mode.
int g_useGUI; 


//Messages support.
unsigned long g_new_message;
unsigned long g_next_app;       // Procedure adreess.
unsigned long g_proc_status;    // Procedure status.


//Drivers support.
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
unsigned long KernelSize;
unsigned long KernelHeapSize;
unsigned long KernelStackSize;
unsigned long KernelPages;
unsigned long KeInitPhase;
unsigned long KernelStatus;
//...


//Task support variables.

//??
unsigned long kernel_switch;


//#bugbug
//move this to kernel (ring 0) crt support.
//error support.
unsigned long errno;


//
// fs support.
//

//directory entries support.
//char buffer_dir_entry[512];

//log buffer
//char KernelLogBuffer[512];



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



//node od a linked list.
struct node_d
{
    void *data;

    //struct window_d *window;
    //int msg;	
    //unsigned long long1;
    //unsigned long long2;
    
    struct node_d *flink;
    struct node_d *blink;    
};


//Linked list support.
struct linkedlist_d
{
    struct node_d *head;
    struct node_d *tail;
};


//save args support. 
struct kernel_args_d
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
}; 
struct kernel_args_d KernelArgs;


//system classes.
struct system_classes_d
{
    //unsigned long Gramado; //@todo: Include this one.
    unsigned long Executive;
    unsigned long Microkernel;
    unsigned long Hal;
};
struct system_classes_d SystemClasses;


//Kernel classes.
struct kernel_classes_d
{
    struct system_classes_d *System;
    //..
};
struct kernel_classes_d KernelClasses;
//...



/*
//Kernel Manager.
struct kernel_d
{
    //
    // Kernel info.
    //

    char *name;
    unsigned long address;

    //Kernel information block.
    //struct kernel_block_d *KernelBlock;

    //struct process_d *process;

    //
    // Structs.
    //

    //struct bootmanager_d     *BootManagerBlock;  //Boot Manager.
    //struct bootloader_d      *BootLoaderBlock;   //Boot Loader.
	
    //struct system_d          *SystemBlock;       //System.
    //struct ProcessorBlock_d  *ProcessorBlock;    //Processor info.
    //...

    //
    // CPUs.
    //

    //int processorCount;
    //struct processor_d *processor;
    
	
    //kernel_args_t
    //kernel_classes_t

    //...
};
struct kernel_d *KernelInfo; 
*/
//...



/*
 **********************************************************
 * plataform_d:
 *     Basic machine components. Hardware and Software. */

struct platform_d
{
    char *name;
    
    // UP or MP;
    SystemType_t system_type;

    struct hardware_d *Hardware;    // hal/hal.h
    struct firmware_d *Firmware;    // hal/hal.h
    struct system_d   *System;      // execve/sm/system.h

    //kernel struct ...
    //struct kernel_d *Kernel;
};
struct platform_d *Platform; 




#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...

//#define CURRENT_ARCH_ARM      2000
//...



// inicialização do kernel, independente da arquitetura.
// See: kernel/main.c
int kernel_main (int arch_type);

//inicialização da arquitetura x86.
int x86main (void);
//...



//Save args in the structure.
void save_kernel_args (void);    


// Linked list support.

void* newLinkedlist (void);
void* newNode (void);

void Removing_from_the_beginning(struct linkedlist_d *list);
void Removing_from_the_middle(struct linkedlist_d *list);
void Removing_from_the_end(struct linkedlist_d *list);


//
// Count support.
//

//?? somente o protótipo. deletar.
//unsigned long get_tick_count ();


//
// Delay support.
//

void sleep (unsigned long ms);


//
// Finalizations support.
//

void faults (unsigned long number);



//
// Error support
// 

// panic without clean
void panic ( const char *format, ... );   //panic.c

// clean and panic.
void panic2 ( const char *format, ... );   //panic.c

void abort (void);    //abort.c
void die (void);      //system.c



//
// End.
//







