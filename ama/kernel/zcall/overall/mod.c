
// mod.c
// see: gramado/mod.h
// see: kernel.h

#include <kernel.h>

// Modulo 0.
// see: kernel.h
struct kernel_module_d  *kernel_mod0;

unsigned long kmList[KMODULE_MAX];


// mod0: Call the entrypoint of the module.
// mod0.bin entry point.
// When this module was loaded? <<<
// see: I_x64CreateKernelProcess in x64init.c
// see: control/newm0/
// Vamos testar um modulo que ja foi carregado previamente?

void test_mod0(void)
{
    unsigned long return_value=0;

    printf ("test_mod0:\n");

    if ((void*) kernel_mod0 == NULL)
        return;
    if (kernel_mod0->magic != 1234)
        return;
    if (kernel_mod0->initialized != TRUE)
        return;

// #test
// Calling the virtual function, and
// getting the return value.
    if ( (void*) kernel_mod0->entry_point != NULL )
    {

        /*
        // #test
        // Testing the parameters. (OK)
        return_value = 
            (unsigned long) kernel_mod0->entry_point(
                                8888,  //reason
                                2020,
                                3030,
                                4040 );
        printf ("RETURN: %d\n",return_value);
        */

        // --------------------
        // Reason 1000: Initializing the module.
        return_value = 
            (unsigned long) kernel_mod0->entry_point(1000,1234,0,0);
        printf ("RETURN: %d\n",return_value);
        

        // --------------------
        // Reason 1001: Testin printf function.
        return_value = 
            (unsigned long) kernel_mod0->entry_point(1001,1234,0,0);       
        printf ("RETURN: %d\n",return_value);
    }
}

void xp_putchar_in_fgconsole(unsigned long _char)
{
    int c = (int) (_char & 0xFF);

// Draw and refresh.
    console_outbyte2 ( c, fg_console );
}

void xp_refresh_screen(void)
{
    refresh_screen();
}

void xp_reboot(void)
{
    keReboot();
}

void xp_putchar_test(void)
{
    int c='x';
    console_outbyte2( c, fg_console );
}

void xp_die(void)
{
    printf("xp_die:\n");
    keDie();
}


