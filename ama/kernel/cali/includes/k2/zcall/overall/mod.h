
// mod.h
// see: mod.c

#ifndef __GRAMADO_MOD_H
#define __GRAMADO_MOD_H    1

#define KMODULE_MOD0  0   // first of the list.
#define KMODULE_MAX   8

// Cross Pointer
#define XP_MOD0    0x30A01000


// Informações compartilhadas 
// entre o kernel e um dado módulo.
struct km_shared_info_d
{
// The entry point
    unsigned long entry_point;
// Procedure.
    unsigned long dialog_address;
// The pointer for a table of symbols exported
// by this module.
    unsigned long function_table_address;
};

struct kernel_module_d
{
    int used;
    int magic;
    int id;

    int initialized;

    char name[64];
    size_t name_size;

// Shared info
    struct km_shared_info_d info;
    struct thread_d  *thread;

// #test
// Virtual function
// The entry point for the ring0 kernel module.
// Using the kernel's address espace.
// IN: 4 parameters.
// OUT: unsigned long.
   unsigned long (*entry_point)(unsigned long, unsigned long, unsigned long, unsigned long);

// Navigation
    struct kernel_module_d  *next;
};

// see: mod.c, x64init.c
extern struct kernel_module_d  *kernel_mod0;

// see: mod.c
extern unsigned long kmList[KMODULE_MAX];

//----------------------------------------------


void test_mod0(void);
// xp - Cross Pointers.
void xp_putchar_in_fgconsole(unsigned long _char);
void xp_refresh_screen(void);
void xp_reboot(void);
void xp_putchar_test(void);
void xp_die(void);

#endif   


