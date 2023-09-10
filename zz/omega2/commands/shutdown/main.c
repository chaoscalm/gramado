
// 'shutdown' command for Gramado.
// It shuts down the machine via i/o ports
// if we are running on qemu.
// Environment: ring 3 application.
// Created by Fred Nora.

#include <rtl/gramado.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <libio.h>

#define is_qemu  rtl_is_qemu

static int shutdown_verbose = FALSE;

//
// private functions: prototypes ==============
//

static void __serial_write_char(unsigned char data);
void do_via_qemu(void);

// ===================================

// Vai escrever em uma porta ja inicializada pelo kernel.
static void __serial_write_char (unsigned char data) 
{
    while (( libio_inport8(0x3F8 + 5) & 0x20 ) == 0)
    {
    };

    libio_outport8 ( 0x3F8, (unsigned char) data );
}


void do_via_qemu(void)
{
    debug_print ("SHUTDOWN.BIN: [QEMU] Shutting down\n");

// #todo
// Nesse momento temos que gravar 
// o cache da FAT no disco físico
// antes de desligarmos.
// Senão teremos problemas para ler os novos arquivos depois
// que religarmos.

    //#test
    //save fat
    if (shutdown_verbose == TRUE)
        printf("saving fat...\n");
    sc82( 10008, 0, 0, 0);

    if (shutdown_verbose == TRUE)
        printf("poweroff via qemu\n");
    libio_outport16(
        (unsigned short) 0x604, 
        (unsigned short) 0x2000 );
}

// main:
// #test
// Testing shutdown in virtual machines.
// #todo:
// We can ask the system if we are in qemu or not.
// See: https://wiki.osdev.org/Shutdown
// #todo: parameters.
// Or maybe we need a application called poweroff.bin.
// Na verdade essa rotina precisa ser em ring0.
// Pois tem que checar a permissão de superuser,
// acionar os locks, sincronizar os sistemas de arquivo
// montados, etc ...
// #todo
// Podemos testar para outros hv, como kvm ...
int main(int argc, char *argv[])
{
    static int isQEMU = FALSE;
    //int isVirtualBox = FALSE;
    //int isBochs      = FALSE;
    register int i=0;
    int fSilent = FALSE;


    for (i=1; i<argc; i++)
    {
        if ( strncmp(argv[i],"--silent",8) == 0 )
            fSilent=TRUE;
        //if ( strncmp(argv[i],"--silent",8) == 0 )
            //fSilent=TRUE;
    };

//
// Flags
//

    shutdown_verbose = TRUE;
    if (fSilent == TRUE)
    {
        shutdown_verbose = FALSE;
        
        //#debug
        //printf("verbose\n");
        //exit(0);
    }

// ==============================
// qemu
// In newer versions of QEMU, you can do shutdown with:
    isQEMU = (int) is_qemu();
    if (isQEMU == TRUE)
    {
        do_via_qemu();
    }

// =========================
// virtualbox
// In Virtualbox, you can do shutdown with:
    //if (isVirtualBox == TRUE){
    //    libio_outport16(0x4004, 0x3400);
    //}

    // bochs
    // In Bochs, and older versions of QEMU(than 2.0), you can do the following:
    //if (isBochs == TRUE){
    //    libio_outport16(0xB004, 0x2000);
    //}

fail:
    printf ("shutdown: FAIL\n");
    if (isQEMU != TRUE){
        printf ("Not running on qemu.\n");
    }
    exit(0);
    return (int) (-1);
}


