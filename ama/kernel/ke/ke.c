
// ke.c (Kernel Executive)
// ke subsystem.

#include <kernel.h>

// ==========================

//
// Import from linker
//

// Não queremos um tamanho de imagem que
// exceda o tamanho da região de memória mapeada para ela.
// No futuro poderemos usar as informações que estão dentro
// do header ELF.
// See: link.ld
static int ImportDataFromLinker = TRUE;

extern unsigned long start_of_kernel_image(void);
extern unsigned long end_of_kernel_image(void);

extern unsigned long kernel_begin(void);
extern unsigned long kernel_end(void);

extern unsigned long code_begin(void);
extern unsigned long code_end(void);

extern unsigned long rodata_begin(void);
extern unsigned long rodata_end(void);

extern unsigned long data_begin(void);
extern unsigned long data_end(void);

extern unsigned long bss_begin(void);
extern unsigned long bss_end(void);

// ==========================

static unsigned long KernelImageSize=0;

static unsigned long KernelImage_Size=0;
static unsigned long KernelImage_CODE_Size=0;
static unsigned long KernelImage_RODATA_Size=0;
static unsigned long KernelImage_DATA_Size=0;
static unsigned long KernelImage_BSS_Size=0;

// ==========================


//-------------

static void __check_refresh_support(void);
static void __print_resolution_info(void);
static void __check_gramado_mode(void);
static void __import_data_from_linker(void);
//-------------------

// Worker
static void __check_refresh_support(void)
{
// Check if we can use refresh_screen or not.

// -------------------------------------------

// No refresh screen yet!
// Ainda nao podemos usar o refresh screen porque a
// flag refresh_screen_enabled ainda nao foi acionada.
// Eh o que vamos fazer agora,
// de acordo com o tamanho da memoria disponivel pra isso.

// ++
// ======================================
// Screen size
// #importante
// Essa rotina calcula a memória que precisamos
// e nos diz se podemos usar o refresh screen.
// Isso habilita o uso do console como verbose para log.

    unsigned long bytes_per_pixel = 0;
    unsigned long pitch = 0;

    refresh_screen_enabled = FALSE;
    screen_size_in_kb = 0;

// #bugbug
// Para os outros casos o pitch será '0'.

    if ( xBootBlock.bpp == 24 || 
         xBootBlock.bpp == 32 )
    {
        bytes_per_pixel = (xBootBlock.bpp / 8); 
        pitch = 
            (unsigned long) (xBootBlock.deviceWidth * bytes_per_pixel);
    }  

// pitch fail,
// don't stop, the real machine needs some kind of
// message support.

    if (pitch == 0){
        refresh_screen_enabled = FALSE;
        debug_print("Screen size fail. pitch\n");
    }

// ---------------

// Saving:
// Screen size in kb.
// Remember: For now we only have 2048KB mapped for LFB.
// Quantos KB vamos precisar para uma tela nessa resoluçao?
    screen_size_in_kb = 
        (unsigned long) (( pitch * xBootBlock.deviceHeight )/ 1024 );

    // #debug
    //printf ("Screen size: %d KB\n", screen_size_in_kb);
 
// Se a quantidade usada por uma tela nessa resoluçao
// for maior que o que temos disponivel.
// Entao nao podemos habilitar o refresh screen.

    if (screen_size_in_kb >= 2048)
    {
        refresh_screen_enabled = FALSE;
        debug_print ("Screen size fail screen_size_in_kb\n");
    }

// ok
// Ok We can use the refresh routine.
// Because we have memory enough for that.

    if (screen_size_in_kb < 2048){
        refresh_screen_enabled = TRUE;  
    }
    
// ======================================
// --

//
// Full console initialization.
//

// We can't live without this.
// But the real machine needs the message support,
// so, we can't stop here. Let's hack for a now.

/*
    if ( refresh_screen_enabled != TRUE )
    {
        debug_print("kernel_main: refresh_screen_enabled != TRUE\n");
        Initialization.is_console_log_initialized = FALSE;
        while(1){asm("hlt");};
        //die(); //we dont have refresh screen support,
    }
*/

// #hack
// #bugbug
// Nesse caso a rotina de refreshscreen vai usar
// um tamanho falso de tela, bem pequeno, que
// cabe na memoria mapeada disponivel.
// Isso sera usado para debug em ambiente
// que tivermos problemas.
// tudo isso se resolvera quando mapearmos memoria
// o suficiente para resoluçoes grandes.

// #todo
// (Screen Extents)
// #todo: 
// We can use the concept of screen extents in this case. 
// It's similar to virtual screens. :)

    if (refresh_screen_enabled != TRUE)
    {
        // Enough for 320x200x32bpp
        fake_screen_size_in_kb = (( 320*4*200 )/1024);
        g_use_fake_screen_size = TRUE;
        refresh_screen_enabled = TRUE;
    }

// -------------------------------------------

}

// Worker
static void __print_resolution_info(void)
{
// Print device info.
    printf ("Width:%d Height:%d BPP:%d\n",
        xBootBlock.deviceWidth,
        xBootBlock.deviceHeight,
        xBootBlock.bpp );
// ---------------
// Is it supported?
// #temp
// Supported widths. 800, 640, 320.
    if ( xBootBlock.deviceWidth != 800 &&
         xBootBlock.deviceWidth != 640 &&
         xBootBlock.deviceWidth != 320 )
    {
        panic("__print_resolution_info: Unsupported resolution\n");
    }
}

// Worker
// CAlled by booting_begin().
static void __check_gramado_mode(void)
{
//-----------
// gramado mode.

// Show gramado mode.
    printf ("gramado mode: %d\n",current_mode);
    
    // #debug
    //refresh_screen();
    //while(1){}

    switch (current_mode){
// #temp
// Supported gramado mode.
    case GRAMADO_JAIL:
    case GRAMADO_P1:
    case GRAMADO_HOME:
        // OK
        break;
// #temp
// Unsupported gramado mode. (yet)
    case GRAMADO_P2:
    case GRAMADO_CASTLE:
    case GRAMADO_CALIFORNIA:
        // #bugbug: panic and x_panic are not working at this point.
        debug_print("__check_gramado_mode: Unsupported gramado mode\n");
        panic("__check_gramado_mode: Unsupported gramado mode\n");
        //x_panic("x");
        //die();
        break;
// Undefined gramado mode.
    default:
        // #bugbug: panic and x_panic are not working at this point.
        debug_print("__check_gramado_mode: Undefined gramado mode\n");
        panic("__check_gramado_mode: Undefined gramado mode\n");
        break;
    };

    // Breakpoint
    //refresh_screen();
    //while(1){}
}

// ================================

static void __import_data_from_linker(void)
{
// #todo
// Isso deve ter uma flag no aquivo de configuração.
// config.h i guess.

    if ( ImportDataFromLinker == TRUE )
    {
        //printf("\n");
 

        //KernelImageSize = (start_of_kernel_image - end_of_kernel_image);
        //printf ("Image Size %d KB \n",KernelImageSize/1024);

        //-------------

        // Não queremos um tamanho de imagem que
        // exceda o tamanho da região de memória mapeada para ela.

        KernelImage_Size = (kernel_end - kernel_begin);
        //printf ("Image Size %d KB \n",KernelImage_Size/1024);

        // .text
        KernelImage_CODE_Size = (code_end - code_begin);
        //printf ("CODE Size %d KB \n",KernelImage_CODE_Size/1024);

        // .rodata
        KernelImage_RODATA_Size = (rodata_end - rodata_begin);
        //printf ("RODATA Size %d KB \n",KernelImage_RODATA_Size/1024);

        // .data
        KernelImage_DATA_Size = (data_end - data_begin);
        //printf ("DATA Size %d KB \n",KernelImage_DATA_Size/1024);

        // .bss
        KernelImage_BSS_Size = (bss_end - bss_begin);
        //printf ("BSS Size %d KB \n",KernelImage_BSS_Size/1024);

        // Limit 1 MB
        // The kernel image is too long.
        if ( KernelImage_Size/1024 > 1024 )
        {
            panic ("Error 0x04: Image size");
        }
        
        // Address limit for the kernel image.
        // See: x64gva.h
        if( kernel_end > KERNEL_HEAP_START )
        {
            panic ("Error 0x04: kernel_end");
        }

        // #debug: breakpoint
        //refresh_screen();
        //while(1){}
    }
}


int keCloseInitProcess(void)
{
    if ((void*) InitThread == NULL){
        goto fail;
    }
    if (InitThread->magic != 1234){
        goto fail;
    }

    // #debug
    printf("#test: Sending CLOSE to init.bin\n");
    refresh_screen();

// Send
    post_message_to_tid(
        (tid_t) 0,                //sender tid. #todo
        (tid_t) InitThread->tid,  //receiver tid.
        (int) MSG_CLOSE,          //msg code
        0,
        0 );

    return 0;
fail:
    return -1;
}

void keReboot(void)
{
    hal_reboot();
}

void ke_x64ExecuteInitialProcess(void)
{
    I_x64ExecuteInitialProcess();
    panic("keInitialize: phase 3\n");
    //goto InitializeEnd;
}

// OUT: TRUE or FALSE.
int keInitialize(int phase)
{
    int Status=FALSE;

    if (phase == 0){

        //PROGRESS("keInitialize: phase 0\n");
        // kernel font.
        zero_initialize_default_kernel_font();
        // Initializing background for the very first time.
        zero_initialize_background();
        // Setup refresh/flush support.
        // Flush data into the lfb.
        __check_refresh_support();
        // Now we have console debug
        Initialization.is_console_log_initialized = TRUE;

        // Show banner!
        zero_show_banner();
        // Print resolution info
        __print_resolution_info();
        // Check gramado mode
        __check_gramado_mode();
        // Import data from linker.
        __import_data_from_linker();

        // Initialize bootloader display device.
        bldisp_initialize();

        goto InitializeEnd;

    } else if (phase == 1) {

        //PROGRESS("keInitialize: phase 1\n");
        // Initialize the current architecture.
        // See: ke/x86_64/x64init.c
        Status = (int) I_x64main();
        if (Status != TRUE){
            goto fail;
        }

        goto InitializeEnd;

    } else if (phase == 2){

        // ================================
        // Early ps/2 initialization.
        // Initializing ps/2 controller.
        // #todo: 
        // Essa inicialização deve ser adiada.
        // deixando para o processo init fazer isso.
        // Chamaremos essa inicialização básica nesse momento.
        // A inicialização completa será chamada pelo processo init.
        // See: i8042.c
        // ================
        // Early initialization
        // Only the keyboard.
        // It is working
        // ================
        // This is the full initialization.
        // #bugbug This is a test yet.
        // It fails in the real machine.

        PROGRESS(":: Early PS2 initialization\n"); 
        PS2_early_initialization();
        //PS2_initialization();

        //================================
        // Initialize all the kernel graphics support.
        // Initialize all the kernel graphics support.
        // some extra things like virtual terminal and tty.
        // #todo: rever essa inicializaçao.
        // See: graphics.c
        // ================================
        // Initialize window server manager.
        // ws.c
        // #debug:  
        // Esperamos alcaçarmos esse alvo.
        // Isso funcionou gigabyte/intel
        // Vamos avançar
        // Quem chamou essa funçao foi o começo da inicializaçao do kernel.
        // Retornamos para x86main.c para arch x86.
        // See: drivers/ws.c
        // Initialize ws callback support.
        // see: callback.c

        PROGRESS(":: kgws, ws, ws callback\n"); 
        // Graphics infrastruture.
        KGWS_initialize();
        // ws registration support.
        ws_init();
        // ws callback support.
        initialize_ws_callback_info();

        // Final message before jumping to init process.
        //PROGRESS("keInitialize: phase 2\n");
        //printf("keInitialize:  phase 2\n");
        //#debug
        //refresh_screen();
        //while(1){}
        // Clear the screen again.
        zero_initialize_background();
        // Loading .BMP icon images.
        //PROGRESS("::(2)(?) Icons\n"); 
        windowLoadGramadoIcons();

        // ==========================
        // Network support.
        // See: network.c
        networkInit();
        PROGRESS("networkInit ok\n"); 

        goto InitializeEnd;
    }

InitializeEnd:
    return TRUE;
fail:
    debug_print("keInitialize: fail\n");
    return FALSE;
}

