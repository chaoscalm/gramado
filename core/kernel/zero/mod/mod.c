
// mod.c
// see: gramado/mod.h
// see: kernel.h

#include <kernel.h>

// Cross Pointer
#define XP_MOD0    0x30A01000

// Modulo 0.
// see: kernel.h
struct kernel_module_d  *kernel_mod0;


unsigned long kmList[KMODULE_MAX];


static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 );

// ----------------------------------------


static void 
caller1(
    unsigned long function_address, 
    unsigned long data0 )
{
// #todo
// + Maybe return 'unsigned long'.
// + Maybe share data via shared memory
//   using a big buffer for that.
// + Maybe share the pointer of the buffer of a file.
// ...
// (in order: rdi, rsi, rdx, rcx, r8, r9).

    //#debug
    //asm (" movq $65, %rdi ");

// 64bit
    unsigned long first_parameter = data0;
    unsigned long return_value=0;
    asm volatile ("movq    %1, %%rax  ;"
         "movq %%rax, %0     ;"
         "movq %%rax, %%rdi  ;"  // RDI: First parameter.  (data0).
         "movq %%rax, %%rsi  ;"  // RSI: Second parameter. (data0).
         :"=r"(return_value)  //output 
         :"r"(first_parameter) //input (O operando eh um registrador de prop. geral).
         :"%rax"   //clobbered register. (rax sera modificado).
    );    
    asm volatile ("call *%0" : : "r"(function_address));

// #test
// #todo
// What is the return value.
    printf ("RETURN: {%d}\n",return_value);
    refresh_screen();
}

// mod0: Call the entrypoint of the module.
// mod0.bin entry point.
// When this module was loaded? <<<
// see: I_x64CreateKernelProcess in x64init.c
// see: control/newm0/
// Vamos testar um modulo que ja foi carregado previamente?

void test_mod0(void)
{
    printf ("test_mod0:\n");
    if ((void*) kernel_mod0 != NULL)
    {
        if (kernel_mod0->magic == 1234)
        {
            if (kernel_mod0->initialized == TRUE)
            {
                //while(1){
                // No return value.
                // 1 parameter.
                // reason=1000. (Initialize)
                caller1((unsigned long) XP_MOD0, 1000 );
                // reason=1001. (test)
                caller1((unsigned long) XP_MOD0, 1001 );
                // Invalid reason
                caller1((unsigned long) XP_MOD0,  999 );
                //};
            }
        }
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
    hal_reboot();
}

void xp_putchar_test(void)
{
    int c='x';
    console_outbyte2 ( c, fg_console );
}

void xp_die(void)
{
    printf("xp_die:\n");
    die();
}





