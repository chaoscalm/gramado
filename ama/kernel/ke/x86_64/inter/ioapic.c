
// ioapic.c
// Document created by Fred Nora - (2023)
// Credits:
//   + Ported from Sirius-x86-64, created by Nelson Cole.


#include <kernel.h>

// Initialization control.
struct ioapic_info_d  IOAPIC;

#define IOAPIC_NULL  0

// #todo
// I/O APIC
// see: ioapic.h
struct __IOAPIC_REDIR_TBL ioapic_redir_table[24];

// #todo
static unsigned long ioapic_base=0;

// ----------------------------------------

static int 
__set_ioapic_redir_table(
    int n,
    unsigned char vector,
    unsigned char delv_mode,
    unsigned char dest_mode,
    unsigned char delv_status,
    unsigned char pin_polarity,
    unsigned char remote_IRR,
    unsigned char trigger_mode,
    unsigned char mask,
    unsigned char destination);

static unsigned int read_ioapic_register(int reg);
static void write_ioapic_register(int reg, unsigned int val);
static int ioapic_configuration(int maximum_redirection);
static int __setup_ioapic(void);

// ----------------------------------------

// read
static unsigned int read_ioapic_register(int reg)
{
    if (IOAPIC.initialized != TRUE)
        panic("read_ioapic_register: depends on IOAPIC.initialized\n");


// The base is a local pointer.
    *(volatile unsigned char*)(ioapic_base + IO_APIC_IND) = reg;

    return ( *(volatile unsigned int*)(ioapic_base + IO_APIC_DAT));
}

// write
static void write_ioapic_register(int reg, unsigned int val)
{
    if (IOAPIC.initialized != TRUE)
        panic("write_ioapic_register: depends on IOAPIC.initialized\n");

// The base is a local pointer.
    *(volatile unsigned char*)(ioapic_base + IO_APIC_IND) = reg;
    *(volatile unsigned int*) (ioapic_base + IO_APIC_DAT) = val;
}



int ioapic_masked(int n)
{
// This pointer is define into this document.
    unsigned long pointer = (unsigned long) &ioapic_redir_table;

// Chech the range.
    if (n<0 || n>=24)
        panic("ioapic_masked: n\n");

    ioapic_redir_table[n].mask = 1;

    unsigned int *data = (unsigned int*) pointer;

    write_ioapic_register(
        IO_APIC_REDIR_TBL(n),
        *(unsigned int*)(data + (n *2)) );

    return 0;
}

int ioapic_umasked(int n)
{
// This pointer is define into this document.
    unsigned long pointer = (unsigned long) &ioapic_redir_table;

// Chech the range.
    if (n<0 || n>=24)
        panic("ioapic_umasked: n\n");

    ioapic_redir_table[n].mask = 0;

    unsigned int *data = (unsigned int*) pointer;
    write_ioapic_register(
        IO_APIC_REDIR_TBL(n),
        *(unsigned int*)(data + (n *2)) );

    return 0;
}

static int 
__set_ioapic_redir_table(
    int n,
    unsigned char vector,
    unsigned char delv_mode,
    unsigned char dest_mode,
    unsigned char delv_status,
    unsigned char pin_polarity,
    unsigned char remote_IRR,
    unsigned char trigger_mode,
    unsigned char mask,
    unsigned char destination)
{

// #warning
// The redirection table is define here in this document.
    unsigned long pointer = (unsigned long) &ioapic_redir_table;

    unsigned int *data = (unsigned int*) pointer;


// Invalid entry
// range: (0~23)
    if (n >= 24)
        panic("__set_ioapic_redir_table: n\n");


// Fill the entry.

    ioapic_redir_table[n].vector = 
        vector;

    ioapic_redir_table[n].delv_mode = 
        delv_mode;

    ioapic_redir_table[n].dest_mode = 
        dest_mode;

    ioapic_redir_table[n].delv_status = 
        delv_status;

    ioapic_redir_table[n].pin_polarity = 
        pin_polarity;

    ioapic_redir_table[n].remote_IRR = 
        remote_IRR;

    ioapic_redir_table[n].trigger_mode = 
        trigger_mode;

    ioapic_redir_table[n].mask = 
        mask;

    ioapic_redir_table[n].destination = 
        destination;

// ------------------------------------
// see this macro in: ioapic.h
// #todo:
// Explain it better.

    write_ioapic_register(
        IO_APIC_REDIR_TBL(n), 
        *(unsigned int*)(data + (n *2)) );

    write_ioapic_register(
        IO_APIC_REDIR_TBL(n) + 1,
        *(unsigned int*)(data + (n *2) + 1) );

// done
    return 0;
}

static int ioapic_configuration(int maximum_redirection)
{
// Fill the table.

    // 24
    int Max = (int) maximum_redirection;

    if (Max < 0)
       panic("ioapic_configuration: Max\n");
// Invalid range
    if (Max > 24)
        panic("ioapic_configuration: Max\n");


    if (LAPIC.initialized != TRUE)
        panic("ioapic_configuration: It depends on LAPIC.initialized\n");

    unsigned int id = (unsigned int) LAPIC.local_id;

// --------------------------
// Install 24 entries
// starting at '0x40'. Why?

    register int i=0;
    for (i=0; i<Max; i++) 
    {
            if (i == 11){
            }
            // else
            
            // Escrene na tabela e configura registradores.
	        __set_ioapic_redir_table(
	            i,         // IRQn
	            0x40 + i,  // vector
	            0,         // Delivery Mode
	            0,         // Destination Mode
	            0,         // RO
	            0,         // Interrupt Input Pin Polarity
	            0,         // RO
	            0,
	            1,         // masked 
	            id );      // lapic id.

    };

    return 0;
}


static int __setup_ioapic(void)
{
    if (IOAPIC.initialized != TRUE)
        panic("__setup_ioapic: It depends on IOAPIC.initialized\n");


// -------------------------
// Save the virtual address of the base of the registers 
// into a local pointer.
    ioapic_base = (unsigned long) IOAPIC.ioapic_va;
    if (ioapic_base == 0)
        panic("__setup_ioapic: ioapic_base\n");


// -------------------------
// Get the 'Maximum redirection' entry.
// We're gonna use it bellow.
    int MaximumRedirection = 
        ((read_ioapic_register(IO_APIC_VER) >> 16) & 0xff) + 1;

// -------------------------
// Set the id of the lapic.
    if (LAPIC.initialized != TRUE)
        panic("__setup_ioapic: It depends on LAPIC.initialized\n");
    unsigned int id = (unsigned int) LAPIC.local_id;
    write_ioapic_register(IO_APIC_ID,id);

// -------------------------
// Fill the table.
// Out of range
    if (MaximumRedirection > 24)
        panic("__setup_ioapic: MaximumRedirection\n");

    ioapic_configuration(MaximumRedirection);

    return 0;
}


void enable_ioapic(void)
{
// Called by I_kmain() in main.c.

    printf("enable_ioapic:\n");

// It depends on LAPIC.
    if (LAPIC.initialized != TRUE)
        panic ("enable_ioapic: It depends on LAPIC.initialized\n");

// Not initialized yet.
    IOAPIC.initialized = FALSE;

// ===================
// Mapping

// page table
// Isso serve pra pegarmos um endereço físico
// que servira de base para criarmos uma pagetable.
// Mas endereço físico e virtual são iguais nessa região.
// Identidade 1:1.
    unsigned long *pt_ioapic = 
        (unsigned long *) get_table_pointer_va();

// -------------
// pa
// #warning: Hard coded.
// see: ioapic.h
    IOAPIC.ioapic_pa = (unsigned long) (IO_APIC_BASE & 0xFFFFFFFF);

// -------------
// va
// see: x64gva.h
    IOAPIC.ioapic_va = (unsigned long) IOAPIC_VA;

// -------------
// pagedirectory entry
    int pdindex = (int) X64_GET_PDE_INDEX(IOAPIC_VA);
    IOAPIC.entry = (int) pdindex; 

// -------------
// Create the table and include the pointer 
// into the kernel page directory.
// ## Estamos passando o ponteiro para o
// diretorio de paginas do kernel.

    mm_fill_page_table( 
      (unsigned long) KERNEL_PD_PA,      // pd 
      (int) pdindex,                     // entry
      (unsigned long) &pt_ioapic[0],     // pt
      (unsigned long) IOAPIC.ioapic_pa,  // region base (pa)
      (unsigned long) ( PAGE_WRITE | PAGE_PRESENT ) );  // flags=3


// OK, the structure is initialized,
// now this module can use the values in it.
    IOAPIC.initialized = TRUE;

//==========================================

//
// Initialize the interrupts.
//

    __setup_ioapic();
}

