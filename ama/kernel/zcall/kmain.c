
// kmain.c
// This is the first C file, called after the assembly routines.

// This file contains the kernel_main function,
// called by START in 
// entrance/warden/unit0/x86_64/head_64.asm.
// This file and their folder will be the control panel
// for the initialization routine.
// Please put here data we need.
// fake main.c
// We need a fake KERNEL.BIN ELF file that will be used my the
// boot loader.
// The boot loader will load the fake kernel image before
// setting up the long mode and the paging.

// The main subsystem is the window system GWSSRV.BIN.
// The first usermode application is GWS.BIN.
// See:
// GWSSRV.BIN: prestier/gws/server
// GWS.BIN:    prestier/gws/client

// #bsod
// List of errors:
// Error: 0x00 - Unexpected error.
// Error: 0x01 - CURRENT_ARCH_X86_64 initialization fail.
// Error: 0x02 - generic.
// Error: 0x03 - Undefined 'current arch'.
// Error: 0x04 - The kernel image is too long.
// Error: 0x05 - Memory allocation for Display device structure.
// ...



#include <kernel.h>

typedef enum {
    KERNEL_SUBSYSTEM_INVALID,
    KERNEL_SUBSYSTEM_DEV,  // Device drivers
    KERNEL_SUBSYSTEM_FS,   // File systems
    KERNEL_SUBSYSTEM_KE,   // Kernel executive
    KERNEL_SUBSYSTEM_MM,   // Memory manager
    KERNEL_SUBSYSTEM_NET,  // Network
    KERNEL_SUBSYSTEM_USER  // User manager. (um)
}kernel_subsystem_t;

// Local
static kernel_subsystem_t __failing_kernel_subsystem = 
    KERNEL_SUBSYSTEM_INVALID;

//
// Initialization :)
//

// Global
//unsigned long gInitializationPhase=0;

// The initialization structure.
// See: config/superv/kinit.h
struct initialization_d  Initialization;


//char InitialUserProcessName[32] = "INIT.BIN"

// ??
// #bugbug
// Explain it better.
// Someone is setting this variable from another document.
// Change the name.
// See: head_64.asm.
unsigned long magic=0;
unsigned long saved_bootblock_base=0;

// virtual = physical.
#define BootBlockVA    0x0000000000090000
#define bbOffsetLFB_PA  0  // offset 0
#define bbOffsetX       1  // offset 8
#define bbOffsetY       2  // offset 16
#define bbOffsetBPP     3  // offset 24
#define bbLastValidPA   4  // offset 32  // Last valid physical address.
#define bbGramadoMode   5  // offset 40  // jail, p1, home ...
// ...


// See:
// xxxhead.asm
extern void x84_64_initialize_machine(void);



// ================================


//
// == Private functions: Prototypes ========
//

// Preinit routines.
static int preinit(void);
static int preinit_SetupBootblock(void);
static void preinit_Globals(int arch_type);
static void preinit_OutputSupport(void);
static void preinit_Serial(void);


static void kernel_final_messages(void);

// System initialization routines.

static void __enter_debug_mode(void);






static void __enter_debug_mode(void)
{
    if (Initialization.is_serial_log_initialized == TRUE){
        debug_print("__enter_debug_mode:\n");
    }

    if (Initialization.is_console_log_initialized != TRUE)
    {
        if (Initialization.is_serial_log_initialized == TRUE){
            debug_print("__enter_debug_mode: can't use the cirtual console\n");
        }
    }

    if (Initialization.is_console_log_initialized == TRUE)
    {
        //printf("kmain.c: The kernel is in debug mode.\n");
        // kgwm_early_kernel_console();  //#deprecated
        //printf("kmain.c: End of debug mode.\n");
        
        // #panic
        printf("__enter_debug_mode: [PANIC] console log ok\n");
        refresh_screen();
        die();
    }

// #panic
// Oh God.
// Die. No refresh. No message.
    die();
}

// ==========================
// ::(2)(1)(2)
static void preinit_Globals(int arch_type)
{
// We dont have any print support for now.

// Scheduler policies
// Early initialization.
// See: 
// sched.h, sched.c.
    SchedulerInfo.policy = SCHED_RR;
    SchedulerInfo.flags  = (unsigned long) 0;

// Initializing the global spinlock.
    __spinlock_ipc = TRUE;

// IO Control
    IOControl.useTTY = FALSE;        // Model not implemented yet.
    IOControl.useEventQueue = TRUE;  // The current model.
    IOControl.initialized = TRUE;    // IO system initialized.

    // ...
//
// Presence level
//

// See:
// sched.h, sched.c

    // (timer ticks / fps) = level

    //presence_level = (1000/1000);  //level 1;    // 1000   fps
    //presence_level = (1000/500);   //level 2;    // 500    fps
    //presence_level = (1000/250);   //level 4;    // 250    fps
    //presence_level = (1000/125);   //level 8;    // 125    fps
    //presence_level = (1000/62);    //level 16;   // 62,20  fps
    //presence_level = (1000/25);    //level 32;   // 31,25  fps
    //presence_level = (1000/15);    //level 64;   // 15,625 fps 
    //presence_level = (1000/10);    //level 100;   // 10 fps
    //presence_level = (1000/5);     //level 200;   // 5  fps
    // presence_level = (1000/4);     //level 250;  // 4  fps
    //presence_level = (1000/2);     //level 500;   // 2  fps
    //presence_level = (1000/1);     //level 1000;  // 1  fps

    //set_update_screen_frequency(30);
    set_update_screen_frequency(60);
    //set_update_screen_frequency(120);
}

// =========================
// ::(2)(1)(3)
// see: serial.c
static void preinit_Serial(void)
{
// We still don't have any print support yet.
// But at the end of this routine we can use the serial debug.

    int Status=FALSE;
    Status = serial_init();
    if(Status!=TRUE){
        //#bugbug
        //Oh boy!, We can't use the serial debug.
    }
    //PROGRESS("::(2)(1)(3):\n");
    PROGRESS("preinit_Serial: Serial debug initialized\n");
}

// ======================
// ::(2)(1)(4)
static void preinit_OutputSupport(void)
{
// #important: 
// We do not have all the runtime support yet.
// We can't use printf yet.
// We only initialized some console structures,
// not the full support for printf functions.

    //PROGRESS("::(2)(1)(4)\n");
    PROGRESS("preinit_OutputSupport:\n");

// O refresh ainda não funciona, 
// precisamos calcular se a quantidade mapeada é suficiente.
    refresh_screen_enabled = FALSE;

    PROGRESS("preinit_OutputSupport: zero_initialize_virtual_consoles\n");
    zero_initialize_virtual_consoles();

    //debug_print("preinit_OutputSupport: preinit_OutputSupport\n");

// #important: 
// We do not have all the runtime support yet.
// We can't use printf yet.
}

// ===================
// ::(2)(3)
static void kernel_final_messages(void)
{
// Final messages
    if ( Initialization.is_serial_log_initialized == TRUE ){
        PROGRESS("::(2)(3): [final message] FAILURE\n");
    }
    if ( Initialization.is_console_log_initialized == TRUE ){
        printf("init: [final message] FAILURE\n");
        refresh_screen();
    }
}

void init_globals(void)
{
// Architecture independent?
// Not everything here.
// Order: cpu, ram, devices, etc.

    int Status=FALSE;

// smp
    g_smp_initialized = FALSE;
    g_processor_count = 0;

// Profiler
// See: pints.h
// Intel/AMD
// Legacy hardware interrupts (irqs) (legacy pic)
    g_profiler_ints_irq0  = 0;
    g_profiler_ints_irq1  = 0;
    g_profiler_ints_irq2  = 0;
    g_profiler_ints_irq3  = 0;
    g_profiler_ints_irq4  = 0;
    g_profiler_ints_irq5  = 0;
    g_profiler_ints_irq6  = 0;
    g_profiler_ints_irq7  = 0;
    g_profiler_ints_irq8  = 0;
    g_profiler_ints_irq9  = 0;
    g_profiler_ints_irq10 = 0;
    g_profiler_ints_irq11 = 0;
    g_profiler_ints_irq12 = 0;
    g_profiler_ints_irq13 = 0;
    g_profiler_ints_irq14 = 0;
    g_profiler_ints_irq15 = 0;
    // ...
// Interrupção para serviços do sistema.
    g_profiler_ints_gde_services = 0;

// User and group.
    current_user  = 0;
    current_group = 0;

// Security layers.
// User session, room(window station), desktop.
    current_usersession = (int) 0;
    current_room = (int) 0;
    current_desktop = (int) 0;

// Process
    foreground_process = (pid_t) 0;
    //current_process = (pid_t) 0;
    set_current_process(0);  //?

// Thread
    foreground_thread = (tid_t) 0;
    current_thread = (int) 0;

// File system support.
// Type=1 | FAT16.
    g_currentvolume_filesystem_type = FS_TYPE_FAT16;
    g_currentvolume_fatbits = (int) 16;

// Inicializa as estruturas do fluxo padrão.
// Isso vai usar a file table.
    Status = (int) kstdio_initialize();
    if (Status != TRUE){
        panic("init_globals: kstdio_initialize fail\n");
    }

// Screen
// Now we can print strings in the screen.
// Reinitializing ... we already printed the banner.
    screenInit();

    //debug_print("init_globals: [printf] WE HAVE MESSAGES NOW!\n");
    //printf     ("init_globals: [printf] WE HAVE MESSAGES NOW!\n");

// ===================

// The kernel request
// See: request.c
    clearDeferredKernelRequest();
}

// ==============================
// ::(4)(1)(1)
// limitation: No serial debug yet.
// #todo: #bugbug
// We have another BootBlock structure in info.h
static int preinit_SetupBootblock(void)
{
// We don't have any print support for now.

// Magic
// #bugbug: Explain it better.
    unsigned long bootMagic = 
        (unsigned long) (magic & 0x00000000FFFFFFFF); 

// The boot block address. 0x0000000000090000.
// Each entry has 8 bytes.
// virtual = physical.
    unsigned long *xxxxBootBlock = (unsigned long*) BootBlockVA; 

// lfb
// Esse endereço virtual foi configurado pelo bootloader.
// Ainda não configuramos a paginação no kernel.
    unsigned long *fb = (unsigned long *) FRONTBUFFER_VA; 
    fb[0] = 0x00FFFFFF;

// Check magic
// Paint a white screen if magic is ok.
// Paint a 'colored' screen if magic is not ok.
    register int i=0;
// WHITE
    if (bootMagic == 1234){
        for (i=0; i<320*32; i++){ fb[i] = 0xFFFFFFFFFFFFFFFF; };
    }
// COLORED
    if (bootMagic != 1234){
        for (i=0; i<320*32; i++){ fb[i] = 0xFF00FFFFFFF00FFF; };
        //#debug
        //while(1){}
    }

    //#debug
    //while(1){}

// Boot block (local structure)
// Saving the boot block
// Structure in this document.
// We will have a global one in gdef.h

    xBootBlock.lfb_pa        = (unsigned long) xxxxBootBlock[bbOffsetLFB_PA];
    xBootBlock.deviceWidth   = (unsigned long) xxxxBootBlock[bbOffsetX];
    xBootBlock.deviceHeight  = (unsigned long) xxxxBootBlock[bbOffsetY];
    xBootBlock.bpp           = (unsigned long) xxxxBootBlock[bbOffsetBPP];
    xBootBlock.last_valid_pa = (unsigned long) xxxxBootBlock[bbLastValidPA];
    xBootBlock.gramado_mode  = (unsigned long) xxxxBootBlock[bbGramadoMode];
    xBootBlock.initialized = TRUE;

// ------------------------------------------------------

// Gramado mode.
// Gramado mode. (jail, p1, home ...)
// Save global variable.
    current_mode = (unsigned long) xBootBlock.gramado_mode;

    // ...

// resolution
// global variables.
// See: kernel.h
    gSavedLFB = (unsigned long) xBootBlock.lfb_pa;
    gSavedX   = (unsigned long) xBootBlock.deviceWidth;
    gSavedY   = (unsigned long) xBootBlock.deviceHeight;
    gSavedBPP = (unsigned long) xBootBlock.bpp;

// #todo
// Setup the real boot block structure at gdef.h

// Set up private variables in screen.c
    screenSetSize (gSavedX,gSavedY);

// Memory support.

// Last valid physical address.
// Used to get the available physical memory.
    blSavedLastValidAddress = (unsigned long) xBootBlock.last_valid_pa; 
// Memory size in KB.
    blSavedPhysicalMemoryInKB = (blSavedLastValidAddress / 1024);

    return 0;
}

// ==========================
// ::(2)(1)
static int preinit(void)
{
// We don't have any print support for now.
// But here is the moment when we initialize the
// serial debug support.

// Starting the counter.
    Initialization.current_phase = 0;

// ==================

// Checkpoints
    Initialization.phase1_checkpoint = FALSE;
    Initialization.phase2_checkpoint = FALSE;
    Initialization.phase3_checkpoint = FALSE;
    Initialization.hal_checkpoint = FALSE;
    Initialization.microkernel_checkpoint = FALSE;
    Initialization.executive_checkpoint = FALSE;
    Initialization.gramado_checkpoint = FALSE;

// Flags
// We still dont have any log/verbose support.
    Initialization.is_serial_log_initialized = FALSE;
    Initialization.is_console_log_initialized = FALSE;
// The display dirver is not initialized yet,
// but the kernel owns it.
    Initialization.kernel_owns_display_device = TRUE;

// Hack Hack
    VideoBlock.useGui = TRUE;

// ::(2)(1)(1)
// first of all
// Getting critical boot information.
    preinit_SetupBootblock();
// ::(2)(1)(2)
// We do not have serial debug yet.
    preinit_Globals(0);  // IN: arch_type

// ::(2)(1)(3)
// Serial debug support.
// After that routine we can use the serial debug functions.
    preinit_Serial();

// ::(2)(1)(4)
// Initialize the virtual console structures.
// We do not have all the runtime support yet.
// We can't use printf yet.
// #important: 
// We do not have all the runtime support yet.
// We can't use printf yet.
// We only initialized some console structures,
// not the full support for printf functions.
    preinit_OutputSupport();

    return 0;
}

void gramado_shutdown(int how)
{
    //hal_shutdown();
}


// == Idle thread in ring 0  ===============
// #test

// #bugbug
// This thread will start to run at the moment when
// the init process enable the interrupts.

// #suspended
void early_ring0_IdleThread (void)
{

// #danger: Do NOT change this function.
// #bugbug: This thread can't execute complex routine for now.

    //printf("");  //fail

    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        debug_print ("early_ring0_IdleThread: w h\n");
        panic       ("early_ring0_IdleThread: w h\n");
    }

Loop:

// acende
    //backbuffer_draw_rectangle( 0, 0, deviceWidth, 28, COLOR_KERNEL_BACKGROUND );
    //draw_string(8,8,COLOR_YELLOW," Gramado Operating System ");
    //refresh_screen();

// relax
    asm ("sti");
    asm ("hlt");

// apaga
    //backbuffer_draw_rectangle( 0, 0, deviceWidth, 28, COLOR_KERNEL_BACKGROUND );
    //backbuffer_draw_rectangle( 0, 0, deviceWidth, deviceHeight, COLOR_KERNEL_BACKGROUND );  //#bug
    //refresh_screen();

    goto Loop;
}

// --------------------------------
// ::(2)
// See: kernel.h
void I_kmain(int arch_type)
{
// Called by START in startup/head_64.asm.
// This is the first function in C.
// We don't have any print support yet.

    int Status = FALSE;
    __failing_kernel_subsystem = KERNEL_SUBSYSTEM_INVALID;

    //int UseDebugMode=TRUE;  //#bugbug
    int UseDebugMode=FALSE;

// Setup debug mode.
// Enable the usage of the serial debug.
// It is not initialized yet.
// #see: debug.c
    disable_serial_debug();
    if (USE_SERIALDEBUG == 1){
        enable_serial_debug();
    }

    // #hack
    //current_arch = (int) arch_type;
    current_arch = CURRENT_ARCH_X86_64;

//
// Pre-init
//


// Preinit
// We don't have any print support yet.
// We initialized the serial debug support, and console structures, 
// but we still can't use the printf functions.

    system_state = SYSTEM_PREINIT;
    preinit();

//
// Booting
//

    PROGRESS(":: Booting ...\n");
    system_state = SYSTEM_BOOTING;


// boot info
    if (xBootBlock.initialized != TRUE){
        panic ("I_kmain: xBootBlock.initialized\n");
    }

//
// mm subsystem
//

    PROGRESS(":: Initialize mm subsystem\n");

// Initialize mm phase 0.
// + Initialize video support.
// + Inittialize heap support.
// + Inittialize stack support. 
// + Initialize memory sizes.
    PROGRESS(":: Initialize mm phase 0\n");
    Status = (int) mmInitialize(0);
    if (Status != TRUE)
    {
        __failing_kernel_subsystem = 
            KERNEL_SUBSYSTEM_MM;
        if (Initialization.is_serial_log_initialized == TRUE){
            debug_print("I_kmain: mmInitialize phase 0 fail\n");
        }
        goto fail;
    }

// Initialize mm phase 1.
// + Initialize framepoll support.
// + Initializing the paging infrastructure.
//   Mapping all the static system areas.
    PROGRESS(":: Initialize mm phase 1\n");
    Status = (int) mmInitialize(1);
    if (Status != TRUE)
    {
        __failing_kernel_subsystem = 
            KERNEL_SUBSYSTEM_MM;
        if (Initialization.is_serial_log_initialized == TRUE){
            debug_print("I_kmain: mmInitialize phase 1 fail\n");
        }
        goto fail;
    }

    g_module_runtime_initialized = TRUE;

//
// ke subsystem
//

    PROGRESS(":: Initialize ke subsystem\n");

// Initialize ke phase 0.
// + kernel font.
// + background.
// + refresh support.
// + show banner and resolution info.
// + Check gramado mode and grab data from linker.
// + Initialize bootloader display device.
    PROGRESS(":: Initialize ke phase 0\n");
    Status = (int) keInitialize(0);
    if (Status != TRUE)
    {
        __failing_kernel_subsystem = 
            KERNEL_SUBSYSTEM_KE;
        goto fail;
    }

// Initialize ke phase 1.
// + Calling I_x64main to 
//   initialize a lot of stuff from the 
//   current architecture.
// + PS2 early initialization.
    PROGRESS(":: Initialize ke phase 1\n");
    Status = (int) keInitialize(1);
    if (Status != TRUE)
    {
        __failing_kernel_subsystem = 
            KERNEL_SUBSYSTEM_KE;
        goto fail;
    }

// Initialize ke phase 2.
// + Initialize background.
// + Load BMP icons.
    PROGRESS(":: Initialize ke phase 2\n");
    Status = (int) keInitialize(2);
    if (Status != TRUE)
    {
        __failing_kernel_subsystem = 
            KERNEL_SUBSYSTEM_KE;
        goto fail;
    }


// #test
// Creating the legacy pty maste and pty slave.
// see: pty.c
    // #debug
    //printf (":: Creating legacy ptys\n");
    //refresh_screen();

    PROGRESS(":: Create lecacy PTYs\n");
    tty_initialize_legacy_pty();


//
// Runlevel switch:
//

// Enter into the debug console instead of jumpinp 
// into the init thread.
// ::: Initialization on debug mode
// Initialize the default kernel virtual console.
// It depends on the run_level.
// See: kgwm.c
    if (UseDebugMode == TRUE){
        __enter_debug_mode();
    }


//
// The root user
//

// Initialize the user list.
    register int u=0;
    for (u=0; u<USER_COUNT_MAX; u++){
        userList[u] = 0;
    };


// #test
// At this point we already have almost all we need to 
// pass the control to the init process.
// So, lets setup the the user for all the resources we created.

    int UserStatus = FALSE;
    UserStatus = (int) userCreateRootUser();
    if (UserStatus != TRUE)
        panic("I_kmain: on userCreateRootUser\n");

    // #debug Breakpoint
    //refresh_screen();
    //while(1){}

StartSystemEnd:

// The initialization failed.
    if (Status != TRUE)
    {
        kernel_final_messages();
        system_state = SYSTEM_DEAD;
        while (1){
            asm ("cli");
            asm ("hlt");
        };
    }

//
// ireq to init thread.
//

    if (Status == TRUE)
    {
        PROGRESS(":: Execute init thread\n");
        //#debug
        //while(1){}
        ke_x64ExecuteInitialProcess();
    }

// Initialization fail
fail:
// #todo
// Print error info if it is possible.
// + __failing_kernel_subsystem
// + system_state
// ...

    PROGRESS("::(2)(2)(?) Initialization fail\n");
    system_state = SYSTEM_ABORTED;
    x_panic("Error: 0x02");
    die();

// Not reached
    while (1){
        asm ("cli");
        asm ("hlt");
    };
}

//
// End
//









