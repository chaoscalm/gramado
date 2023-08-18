
// shell.bin
// Shell application for Gramado OS.
// This is gonna run on terminal.bin, sending data 
// to it via tty. (stderr for now).

// rtl
#include <types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <rtl/gramado.h>

// Internal routines.
#include "shell.h"

// ================
// Testing (VGA embedded ring3 driver).
// libio
//#include <libio.h>
#include "vga_test.h"
//================

int isTimeToQuit=FALSE;
unsigned long device_width=0;
unsigned long device_height=0;

//======================================

static void shellPrompt(void);
static unsigned long shellCompare(void);
static void doExit(void);
static void doLF(void);

//======================================

static void doExit(void)
{
    printf("doExit(): ");
    fflush(stdout);
    exit(0);
    //isTimeToQuit = TRUE;
}

static void doLF(void)
{
    printf(".\n");
}

/*
 * shellPrompt:
 * Inicializa o prompt.
 * Na inicialização de stdio, 
 * prompt foi definido como stdin->_base.
 */

static void shellPrompt(void)
{
    register int i=0;

// Clean prompt buffer   
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
        prompt[i] = (char) '\0';
    };

// First char
    prompt[0] = (char) '\0';

// Variables
    prompt_pos = 0;
    prompt_status = 0;
    prompt_max = PROMPT_MAX_DEFAULT;

// Draw prompt.

    //printf("\n");
    //putc('$',stdout);
    //putc(' ',stdout);
    //printf("\n");
    //printf("$\n");


    printf("$ ");
    fflush(stdout);
}

// local
static unsigned long shellCompare(void)
{
    unsigned long ret_value=0;
    char *p;

// The first char.
// $(NULL)
// [ENTER] finalizou a atring antes de ter digitado alguma coisa.
// Se alguem pressiona [ENTER] com prompt vazio d� page fault ?
// Isso cancela caso o buffer esteja vazio.

// Local pointer,
    p = prompt;

    //if ((void*) p == NULL)
    //{
    //    printf("p \n");
    //    exit(0);
    //}

// Null string.
    if ( *p == '\0' )
    {
        //shellInsertLF();
        goto exit_cmp;
    }

//
// Compare
//

// Compare strings.
// Let's start at the next line.

do_compare:

    //shellInsertLF();
    //printf("\n");

    // cls
    // #todo: Send escape sequence.
    if ( strncmp(prompt,"cls",3) == 0 )
    {
        //doLF();
        printf ("~cls \n");
        //fflush(stdout);
        goto exit_cmp;
    }
 
    // about
    // #todo: Create do_banner();
    if ( strncmp ( prompt, "about", 5 ) == 0 )
    {
        printf ("shell.bin: This is the shell command\n");
        //fflush(stdout);
        goto exit_cmp;
    }

    // getpid
    int my_pid=0;
    if ( strncmp( prompt, "getpid", 6 ) == 0 )
    {
        my_pid=getpid();
        printf ("pid: %d\n",my_pid);
        goto exit_cmp;
    }

    // getppid
    int my_ppid=0;
    if ( strncmp( prompt, "getppid", 7 ) == 0 )
    {
        my_ppid=getppid();
        printf ("ppid: %d\n",my_ppid);
        goto exit_cmp;
    }

// mm-size (MB)
    unsigned long __mm_size_mb = 0;    
    if ( strncmp( prompt, "mm-size", 7 ) == 0 )
    {
        __mm_size_mb = (unsigned long) gramado_system_call (292,0,0,0);
        printf ("Memory size = %d MB \n",__mm_size_mb);
        goto exit_cmp;
    }

// current-process
    if ( strncmp ( prompt, "current-process", 15 ) == 0 )
    {
        //printf("\n");
        //gramado_system_call ( SYSTEMCALL_CURRENTPROCESSINFO, 0, 0, 0 );
        gramado_system_call ( 80, 0, 0, 0 );
        goto exit_cmp; 
    }

// process-info
    if ( strncmp ( prompt, "process-info", 12 ) == 0 )
    {
        //printf("\n");
        gramado_system_call ( 82, 0, 0, 0 );
        goto exit_cmp; 
    }

// exit
    if ( strncmp( prompt, "exit", 4 ) == 0 ){
        doExit();
        goto exit_cmp;
    }

// quit
    if ( strncmp( prompt, "quit", 4 ) == 0 ){
        doExit();
        goto exit_cmp;
    }

// malloc
    void *hBuffer;
    if ( strncmp( prompt, "malloc", 6 ) == 0 )
    {
        printf ("Testing heap: 32KB\n");
        hBuffer = (void *) malloc( 1024*32 );        // 32 kb
        //...
        if ( (void *) hBuffer == NULL ){
            printf("Fail\n");
        }else{
            printf("OK\n");
        };
        printf("done\n");
        goto exit_cmp;
    }

// sync 
// Salva os buffers em ring0 no disco fisico.
// Isso pode ser um programa.
// See: unistd.c
    if ( strncmp( prompt, "sync", 4 ) == 0 )
    {
        //printf ("sync: \n");
        sync();
        goto exit_cmp;
    }

// tty3
    if ( strncmp ( prompt, "tty3", 4 ) == 0 )
    {
        //if ( isatty(fileno(stdin)) == 0 ){
        //    printf ("stdin is not a tty\n");
        //}
        //if ( isatty(fileno(stdout)) == 0 ){
        //    printf ("stdout is not a tty\n");
        //}
        //if ( isatty(fileno(stderr)) == 0 ){
        //    printf ("stderr is not a tty\n");
        //}
        goto exit_cmp;
    }

launch_app:

    // #todo: Para testes podemos aceitar os
    // comandos com extensao .bin
    //rtl_clone_and_execute(prompt);

    //printf ("Command not found\n");
    printf("SHELL.BIN: Command not found! \n");
    //fflush(stdout);

// #testando escape sequences.
    //printf("Escape \x1b[4B \n");
    //fflush(stdout);
    // ...

exit_cmp:
    ret_value = 0;
done:
    shellPrompt();
    return (unsigned long) ret_value;
}

//
// Main
//

int main(int argc, char *argv[])
{
    register int i=0;
    int C=0;
    isTimeToQuit = FALSE;

// -----------------------------------
// (>>> stdout)
// Still using the kernel console.

    printf("shell.bin: argc={%d} ",argc);
    fflush(stdout);

    if (argc>0)
    {
        for (i=0; i<argc; i++){
            printf("argv[%d]: %s\n", i, argv[i] );
        };
    }

// -----------------------------------
// (>>> stderr)
// Now we have a new stdout.
// Now we're gonna send the data to the terminal.bin
// that is reading stderr.

    stdout = stderr;

// Send a simple string.
    printf("SHELL.BIN: Shell is alive! ");
    fflush(stdout);
    
    shellPrompt();

// ------------------------------------------------
// Loop: (Input events).
// Reading from stdin and sending to our new stdout.
// stderr.

    while (1){

        if (isTimeToQuit == TRUE)
            break;

        // #bugbug
        // We got a PF when we type a lot of keys.
        // And sometimes when we type Enter.

        C = fgetc(stdin);
        // Como estamos usando um arquivo regular,
        // entao o kernel concatena ate chegar no fim do arquivo.
        if (C == EOF){
            //rewind(stdin);
            //exit(0);
        }

        // Valid char.
        if (C>0)
        {
            // [ Enter ]
            if (C == VK_RETURN)
            {
                //printf("%c",'$');
                //fflush(stdout);
 
                // #bugbug #todo: Compare the string.
                shellCompare();
            }

            // Printable chars.
            if (C >= 0x20 && C <= 0x7F)
            {

                // Feed the command line in 'prompt', i guess.
                input(C);

                // #debug
                // O terminal vai imprimir errado.
                // ok funcionou.
                //printf("%c", (C+1) ); 
      
                printf("%c",C);
                fflush(stdout);
                 
                // + precisamos nos certificar que eh o shell
                // que esta enviando chars para o terminal
                // e nao o kernel
                // + precisamos nos certivicar que o shell esta lendo de um arquivo.
                // isso eh uma tentativa
                //if (C == 'q')
                //{
                    //printf("%c",'9');
                    //fflush(stdout);
                    //exit(0);   //#test
                //}
            }
        }
    };

    if (isTimeToQuit != TRUE)
    {
        printf("Quit fail ");
        fflush(stdout);
        while (1){
        } ;
    }

done:
    printf("Quit ok ");
    fflush(stdout);
    return 0;
}


