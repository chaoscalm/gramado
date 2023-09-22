
// sci0.h

#ifndef __SYSCALLS_SCI0_H
#define __SYSCALLS_SCI0_H    1

// The handler is sci0().

#define SYS_NULL  0
#define SCI0_NULL  0  // <<<<<<--- #todo Use this pattern.

// Disk
#define SYS_READ_LBA    1
#define SYS_WRITE_LBA   2
#define SYS_READ_FILE   3
#define SYS_WRITE_FILE  4

// kgws - Graphics
#define SYS_VSYNC                5
#define SYS_BUFFER_PUTPIXEL      6
#define SYS_BUFFER_DRAWCHAR      7
#define SYS_BUFFER_DRAWLINE      8
#define SYS_BUFFER_DRAWRECT      9
// 10 =  Refresh rectangle.
//#define SYS_BUFFER_CREATEWINDOW  10 // (#deprecated)
#define SYS_REFRESHSCREEN        11

// Network
#define SYS_REDE_R1    12
#define SYS_REDE_R2    13
#define SYS_REDE_R3    14
#define SYS_REDE_R4    15

// Posix
#define SYS_OPEN     16  // open()
#define SYS_CLOSE    17  // close()
#define SYS_READ     18  // read()
#define SYS_WRITE    19  // write()

// Buffers support: 20~23
#define SYS_REFRESH_BUFFER1  20
#define SYS_REFRESH_BUFFER2  21
#define SYS_REFRESH_BUFFER3  22
#define SYS_REFRESHSCREEN2   23

// Surface support: 24~28
#define SYS_24  24
#define SYS_25  25
#define SYS_26  26
#define SYS_27  27
#define SYS_28  28


// kgws - Print string on backbuffer.
#define SYS_MY_BUFFER_PRINTSTRING  29

// kgws - Print pixel on backbuffer.
#define SYS_MY_BUFFER_PUTPIXEL   30
#define SYS_MY_BUFFER2_PUTPIXEL  31
#define SYS_MY_BUFFER3_PUTPIXEL  32

// Not in use.
#define SYS_33  33

// Cursor
// Setup cursor position for the current virtual console.
#define SYS_VIDEO_SETCURSOR  34

// Not in use.
#define SYS_35  35

// #deprecated
// O teclado envia essa mensagem para o procedimento ativo.
// #define SYS_KSENDMESSAGE  36  

// #deprecated
// Chama o procedimento padrao do sistema.
// #define SYS_CALLSYSTEMPROCEDURE  37  

// Hostname
#define SYS_GETHOSTNAME  38
#define SYS_SETHOSTNAME  39
// Username
#define SYS_GETUSERNAME  40
#define SYS_SETUSERNAME  41

// #deprecated
// Load bitmap image, size=16x16.
// #define SYS_LOADBMP16X16  42

// Create an empty file
// see: sci0() in sci.c
#define SYS_43  43
// 44 - Create an empty directory.
#define SYS_44  44

// 45 - livre
// #todo: Usar para manipulação de arquivo ou diretório.
#define SYS_45  45

// 46 - livre
// 47 - Show cpu info.
// 48 - livre
// 49 - Show system info.

// ...

// 65 - Put a char in the current virtual console.
#define SYS_KGWS_PUTCHAR  65

//#define SYS_66  66
//#define SYS_67  67
//#define SYS_68  68
//#define SYS_69  69

//
//    Process and Thread 
//


// Process and thread support.
#define  SYS_EXIT             70    // Um thread saiu.
#define  SYS_FORK             71    // fork.
#define  SYS_CREATETHREAD     72    // Create thread and execute it.
#define  SYS_CREATEPROCESS    73    // Create process and execute it. 
#define  SYS_CLOSEALLPROCESS  74    // FECHA TODOS PROCESSO.
#define  SYS_EXECVE           75    // execve 
#define  SYS_GETNEXTPROCESS   76    // get next process
#define  SYS_SETNEXTPROCESS   77
#define  SYS_GETNEXTTHREAD    78    // get next thread.
#define  SYS_SETNEXTTHREAD    79

// Process support.
#define SYS_CURRENTPROCESSINFO  80  // Informações sobre o processo atual.
#define SYS_GETPPID             81  // get parent process id.

// 82 - Show process information.

// Wait 4 PID.
// Wait for process termination.
// A thread atual vai esperar até que um processo termine.
#define SYS_WAIT4PID  83
#define SYS_WAIT4     83

// Not in use.
#define SYS_84  84

// GET CURRENT PROCESS ID.
#define SYS_GETPID  85

// Not in use.
#define SYS_86  86
#define SYS_87  87

// Test process validation.
#define SYS_88  88

// Not in use.
#define SYS_89  89

// ------------------
// 90~99 Reservado para thread support
#define SYS_DEADTHREADCOLLECTOR  90
#define SYS_ALERTTHREAD  91
#define SYS_92  92
#define SYS_93  93
#define SYS_STARTTHREAD  94 //REAL (coloca a thread em standby para executar pela primeira vez.)
#define SYS_95  95
#define SYS_96  96
#define SYS_97  97
#define SYS_RESUMETHREAD  98  //retomar thread.
#define SYS_99  99
// ------------------

// 100~109: free

//---------------
// Reboot
#define SYS_REBOOT  110

// #important
// Get system message.
#define SYS_111  111

// Post message to tid.
// Asynchronous.
#define SYS_112  112

// 113~119: free

//------------

// 120
// Get a message given the index.
// With restart support.
#define SYS_120  120

//#define SYS_121  121
//#define SYS_122  122
//#define SYS_123  123

// #test: a kernel request.
#define SYS_124  124

#define SYS_125  125

// i/o port support
#define SYS_USERMODE_PORT_IN   126
// i/o port support
#define SYS_USERMODE_PORT_OUT  127

// 128~129: free

// --------------------

// 130,131

// 132 - d_draw_char
// Desenha um caractere e pinta o pano de fundo.
#define SYS_132  132
// 133 - d_drawchar_transparent
// Desenha um caractere sem alterar o pano de fundo.
#define SYS_133  133

// 134~136: free

// 137 - #deprecated.
// SUPORTE a getch()
#define SYS_GETCH  137    

// 138 - Get key state.
#define	SYS_138           138

#define	SYS_GETSCANCODE   139  

// -------------------

//keyboard responder
#define	SYS_SET_CURRENT_KEYBOARD_RESPONDER 140
#define	SYS_GET_CURRENT_KEYBOARD_RESPONDER 141
//mouse responder
#define	SYS_SET_CURRENT_MOUSE_RESPONDER 142
#define	SYS_GET_CURRENT_MOUSE_RESPONDER 143
//144-149 Recursos da area do Cliente.
#define	SYS_GETCLIENTAREARECT 144
#define	SYS_SETCLIENTAREARECT 145
// Janelas principais usadas pelo kgws.
#define	SYS_146  146    // retorna o ponteiro para gui->screen 
#define	SYS_147  147    // retorna o ponteiro para gui->main
//grid
#define	SYS_148 148 //create grid
#define	SYS_149 149 //initialize grid.

// -----------------

// 150~156 User and group support.
#define SYS_CREATEUSER         150
#define SYS_SETCURRENTUSERID   151
#define SYS_GETCURRENTUSERID   152
#define SYS_SETCURRENTGROUPID  153
#define SYS_GETCURRENTGROUPID  154
#define SYS_UPDATEUSERINFO     155
#define SYS_SHOWUSERINFO       156

// Security ?
#define SYS_GETCURRENTUSERSESSION    157 // user session
// 158 - free
#define SYS_GETCURRENTDESKTOP        159 // zh?

// ------------

// 160~169: Reserved to network support.
#define SYS_160  160    //create socket (retorna o ponteiro para a estrutura)
#define SYS_161  161    //get socket IP
#define SYS_162  162    //get socket port
#define SYS_163  163    //update socket  
#define SYS_164  164    //netStream
#define SYS_165  165    //netSocket
#define SYS_166  166    //netBuffer
#define SYS_167  167
#define SYS_168  168
#define SYS_169  169 

// -----------------

// Print Working Directory.
// Comand 'pwd'.
#define SYS_PWD  170
// Get current volume id.
#define SYS_GETCURRENTVOLUMEID  171
// Configura o id do volume atual.
#define SYS_SETCURRENTVOLUMEID  172
// Listar os arquivos do diretório. 
// Dados ids de disco, volume e diretório.
#define SYS_LISTFILES  173
// Procurar arquivo. 
#define SYS_SEARCHFILE  174
// 175 - 'cd' command support.
#define SYS_175  175
// 176 - pathname backup string.
#define SYS_176  176
// 'dir' command.
// Listando arquivos em um diretório dado o nome.
#define SYS_177  177
// Get file size.
// Pegando o tamanho de um arquivo.
// bufbug: isso está gastando memória carregando o diretório raiz.
#define SYS_178  178
// Not in use.
#define SYS_179   179

// -----------------

// 180~189: memory support.
// Memory support.
// Precisa de privilágios.
#define SYS_CREATEPAGEDIRECTORY    180  // cria um pagedir.
#define SYS_CREATEPAGETABLE        181  // cria uma pagetable.
#define SYS_SHOWMEMORYSTRUCTS      182  // mostra estruturas de gerencia de memória.
#define SYS_SETCR3                 183  // configura o cr3 do processo atual.
#define SYS_GETPROCESSHEAPPOINTER  184  // pega o heap pointer de um processo.
#define SYS_SETKERNELHEAP          185  // configura o heap do kernel.
#define SYS_ALLOCATEKERNELHEAP     186  // aloca heap do kernel.
#define SYS_FREEKERNELHEAP         187  // Libera heap do kernel.
#define SYS_GETPROCESSDIRECTORY    188  // get process directory.
#define SYS_SETPROCESSDIRECTORY    189  // set process directory.

// 190~199: free

// 200~209: free

// -------------------
// 210~219: terminal/virtual console support.
// #bugbug: 
// Isso provavelmente são rotinas de console virtual
// e não de pseudo terminal
// Terminal emulator support.
#define SYS_CREATETERMINAL          210
#define SYS_GETCURRENTTERMINAL      211
#define SYS_SETCURRENTTERMINAL      212
#define SYS_GETTERMINALINPUTBUFFER  213
#define SYS_SETTERMINALINPUTBUFFER  214
#define SYS_GETTERMINALWINDOW       215
#define SYS_SETTERMINALWINDOW       216
#define SYS_GETTERMINALRECT         217
#define SYS_SETTERMINALRECT         218
#define SYS_DESTROYTERMINAL         219

// -------------------

// --------------

//
// Get info.
//

#define SYS_220  220
#define SYS_222  222
// 223 - Get sys time info.
#define SYS_223  223
//time date
#define SYS_GETTIME 224
#define SYS_GETDATE 225

// Semaphore.
#define SYS_GET_KERNELSEMAPHORE    226  // Get.  
#define SYS_CLOSE_KERNELSEMAPHORE  227  // Close (0).
#define SYS_OPEN_KERNELSEMAPHORE   228  // Open  (1).
#define SYS_229  229  // #todo: use it for semaphore support.

// -------------
// 230~239: Reserved for tty support.

// -------------
// 240~249: Reserved for text editing support.

#define SYS_GETCURSORX  240
#define SYS_GETCURSORY  241
#define SYS_242         242
#define SYS_243         243
#define SYS_244         244
#define SYS_245         245
#define SYS_246  246
#define SYS_247  247
#define SYS_248  248
#define SYS_249  249

// -------------
// (250 ~ 255) - Info support.

// System info support.
#define SYS_GETSYSTEMMETRICS  250    // System metrics. 
#define SYS_SHOWDISKINFO      251    // Current disk.            
#define SYS_SHOWVOLUMEINFO    252    // Current volume.
#define SYS_MEMORYINFO        253    // Memory info.
#define SYS_SHOWPCIINFO       254    // PCI info.
#define SYS_SHOWKERNELINFO    255    // Kernel info.

//
// == Extra ============================================
//

// The handler is the worker __extra_services(), 
// called by sci0().

// 260 read.
// 261 write.
// 262 console read
// 263 console write
// 266 process_get_tty
// 272 tty read
// 273 tty write
// 277 console_get_current_virtual_console
// 278 console_set_current_virtual_console
// 288 Returns the current runlevel.
// 289 Serial debug print string.
// 292 newos_get_memory_size_mb
// 293 info_get_boot_info

/*
 350 sys_initialize_component:
// Inicializar ou reinicializar componentes do sistema
// depois da inicialização completa do kernel.
// Isso poderá ser chamado pelo init.bin, pelo shell
// ou qualquer outro.
*/

// 377 - Get info to fill the utsname structure.

// 391 - backbuffer_draw_rectangle
// #bugbug
// Falha se tentamos pintar a tela toda.


// ws and wm.

// 512 - SYS_GET_WS_PID
// 512 - Get ws PID for a given zh.
// Pega o wm de um dado zh.
#define  SYS_GET_WS_PID  512

// 513 - SYS_SET_WS_PID
// 513
// Register the ring3 display server.
// Set ws PID for a given zh
// Register a display server.
// gramado_ports[11] = ws_pid
// Called by the window server.
// arg2 = zh structure pointer.
// arg3 = The window server PID.
// #todo: 
// We need a helper function for this.
#define  SYS_SET_WS_PID  513

// 514 - SYS_GET_WM_PID
// 514 - get wm PID for a given zh
// IN: zh
#define  SYS_GET_WM_PID  514

// 515 - SYS_SET_WM_PID
// 515 - set wm PID for a given zh
// Register a ring3 wm.
// IN: zh, pid
#define  SYS_SET_WM_PID  515

// Ingo for ws and wm.
#define SYS_SHOW_X_SERVER_INFO  516  // show x server info
#define SYS_SHOW_WM_INFO        517  // show wm info

// 519 - CurrentZingHook
// #bugbug
// This is a ring0 pointer.
// A ring3 process can't handle this thing.
// Get current zh

// 521
// network server
// 521 - set ns PID for a given zh
// Register a network server.
// gramado_ports[11] = ws_pid


// 600 - dup
// 601 - dup2
// 602 - dup3

// 603 - lseek support.
// See: klib/kunistd.c
// IN: fd, offset, whence.

// 640
// Lock the taskswtiching.
// Only the init thread can call this service.

// 641
// Unlock taskswitching.
// Only the init thread can call this service.

// 642
// Lock the scheduler.
// Only the init thread can call this service.

// 643
// Unlock scheduler.
// Only the init thread can call this service.

// 770 - Show device list.

// 777 - cpu usage for idle thread.

// 801 - get host name
// 802 - set host name
// 803 - Get user name.
// 804 - Set user name.


// 808 - __ptsname
// #todo
// supporting ptsname libc function
// get_ptsname
// #todo: Change the name to sys_ptsname()
// IN: fd do master, buffer em ring3 para o nome, buflen.

// (#bugbug: The same as above?)
// 809 - __ptsname
//#todo
//supporting ptsname_r libc function
// #todo: Change the name to sys_ptsname()
//IN: fd do master, buffer e buflen.

// 880 - Get process stats given pid
// 881 - Get thread stats given tid
// 882 - Get process name
// 883 - Get thread name

// 884 - alarm()
// See: sys.c

// 891 - Allocate shared ring3 pages.

// 892 - Setup the thread's surface rectangle.
// 893 - Invalidate the thread's surface rectangle.

// 896 - Invalidate the whole screen
// 897 - Create a rectangle.

// (The kernel console).
// 898 - Enable prompt
// 899 - Desable prompt

// 913 - sys_sleep_if_socket_is_empty
// is the socket full?

// 4444
// Show root files system info.
// Print into the raw kernel console.

// 7000 ~ 7020 for network sockets

// 7000 - socket() 
// 7001 - connect()
// 7002 - accept()
// 7003 - bind()
// 7004 - listen() support.


// 7006 - socket_set_gramado_port
// Salvar um pid em uma das portas.
// IN: gramado port, PID

// 7007 - sys_getsockname()

// 7008 - show socket info for a process.
// 7009 - libc: shutdown() IN: fd, how

// 8000 - ioctl() implementation.

// 8001 - fcntl()

// 8002 - sys_setup_stdin
// ?? #bugbug
// Setup stdin pointer
// See: kstdio
// IN: fd

// 9100 - ui_get_system_icon
// Pegando o endereço de um buffer de icone.
// queremos saber se ele eh compartilhado.
// shared_buffer_terminal_icon
// #bugbug: Static size for the icons. Static buffer size.
// See: wm.c



#endif   








