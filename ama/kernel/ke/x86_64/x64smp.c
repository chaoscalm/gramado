
// x64smp.c
// smp support.
// Initialization
// Probing if smp is supported.
// + Via MP.
// + Via ACPI.
// #todo
// This is a work in progress.
// >> we need to disable PIC, and init the first AP.
// The routines are found in another place. 
// see: apic/ioapic routines.
// 2022: Created by Fred Nora.

#include <kernel.h>


// see: mp.h
struct mp_floating_pointer_structure_d *MPTable;
// see: mp.h
struct mp_configuration_table_d *MPConfigurationTable;
// see: mp.h
struct smp_info_d smp_info;

// ------------------------------------
static int __x64_probe_smp(void);
static int __x64_probe_smp_via_acpi(void);
// ------------------------------------

// x64_probe_smp:
// MP Floating Point Structure:
// To use these tables, the MP Floating Point Structure 
// must first be found. As the name suggests, 
// it is a Floating Point Structure and must be searched for.
// can't be found in this area, 
// then the area between 0xF0000 and 0xFFFFF should be searched. 
// To find the table, the following areas must be searched in:
// :: a) In the first kilobyte of Extended BIOS Data Area (EBDA), or
// :: b) Within the last kilobyte of system base memory 
// (e.g., 639K-640K for systems with 640KB of base memory 
// or 511K-512K for systems with 512 KB of base memory) 
// if the EBDA segment is undefined, or
// :: c) In the BIOS ROM address space between 0xF0000 and 0xFFFFF.
// See:
// https://wiki.osdev.org/Symmetric_Multiprocessing
// OUT:
// TRUE = OK.
// FALSE = FAIL.
// Probe the MP Floating Point structure.
// Called by I_init() in x64init.c.
// It works on qemu and qemu/kvm.
// It doesn't work on Virtualbox. (Table not found).
static int __x64_probe_smp(void)
{
// + Find the processor entries using the MP Floating point table.
// + Initialize local apic.

// 0x040E - The base address.
// Get a short value.
    unsigned short *bda = (unsigned short*) BDA_BASE;
    unsigned long ebda_address=0;
    register int i=0;
    unsigned char *p;
// Signature elements.
    unsigned char c1=0;
    unsigned char c2=0;
    unsigned char c3=0;
    unsigned char c4=0;

    printf("x64_probe_smp:\n");

// #todo
// We can use a structure and put all these variable together,
    g_smp_initialized = FALSE;
    smp_info.initialized = FALSE;

// At this point we gotta have a lot of information
// in the structure 'processor'.
    if ( (void*) processor == NULL ){
        panic("x64_probe_smp: processor\n");
    }
// Is APIC supported?
    if (processor->hasAPIC != TRUE){
        panic("x64_probe_smp: No APIC\n");
    }

//
// Probe ebda address at bda base.
//

    printf("EBDA short Address: %x\n", bda[0] ); 
    ebda_address = (unsigned long) ( bda[0] << 4 );
    ebda_address = (unsigned long) ( ebda_address & 0xFFFFFFFF);
    printf("EBDA Address: %x\n", ebda_address ); 

    // #debug
    // refresh_screen();

//
// Probe 0x5F504D5F signature. 
// "_MP_".
//


// base
// between 0xF0000 and 0xFFFFF.
// #todo: filter

    p = ebda_address;

// The signature was found?
    static int mp_found = FALSE;

// Probe for the signature."_MP_"
// This signature is the first element of the table.
// MP Floating Pointer Structure
    int max = (int) (0xFFFFF - ebda_address);
    for (i=0; i<max; i++){
        c1 = p[i+0];
        c2 = p[i+1];
        c3 = p[i+2];
        c4 = p[i+3];
        if ( c1 == '_' && c2 == 'M' && c3 == 'P' && c4 == '_' )
        {
            printf (":: Found _MP_ at index %d. :)\n",i);
            mp_found=TRUE;
            break;
        }
    };

// Signature not found.
// #todo: Try APIC instead.
    if (mp_found != TRUE)
    {
        printf("x64_probe_smp: MP table wasn't found!\n");
        printf ("Try APIC table instead\n");
        goto fail;
    }


//mp_table_found:

// ==============================================
// MPTable
// MP Floating Point Structure
// base + offset.
// This is the base of the structure.
// See:
// https://wiki.osdev.org/User:Shikhin/Tutorial_SMP
// hal/mp.h

    unsigned long table_address = 
        (unsigned long) (ebda_address + i);
    MPTable = 
        (struct mp_floating_pointer_structure_d *) table_address;

// Saving
    smp_info.mp_floating_point = 
        (struct mp_floating_pointer_structure_d *) MPTable;
// ---------------------------------------------
// Print table info

// Signature
// "_MP_" 
// + OK on qemu.
// + OK on kvm.
// + FAIL on Virtualbox. #todo: try APIC.
    printf("Signature: %c %c %c %c\n",
        MPTable->signature[0],
        MPTable->signature[1],
        MPTable->signature[2],
        MPTable->signature[3] );

    //#debug
    //refresh_screen();
    //while(1){}

// ------------------------------------------
// Getting the address of the MP Configuration Table. 
// Pointed by th MP Floating point structure.
// 32bit address.
    unsigned long configurationtable_address = 
        (unsigned long) (MPTable->configuration_table & 0xFFFFFFFF);

// Pointer for the configuration table.
    printf("Configuration table address: {%x}\n",
        configurationtable_address);
// Lenght: n*16 bytes
// The length of the floating point structure table, 
// in 16 byte units. 
// This field *should* contain 0x01, meaning 16-bytes.
    printf("Lenght: {%d}\n", MPTable->length);
// Revision: 1.x
// The version number of the MP Specification. 
// A value of 1 indicates 1.1, 4 indicates 1.4, and so on.
    printf("Revision: {%d}\n", MPTable->mp_specification_revision);
// Checksum
// The checksum of the Floating Point Structure. 
    printf("Checksum: {%d}\n", MPTable->checksum);
// Default configuration flag.
// If this is not zero then configuration_table should be 
// ignored and a default configuration should be loaded instead.
    printf("Default configuration flag: {%d}\n",
        MPTable->default_configuration );

    if ( MPTable->default_configuration != 0 ){
        printf("todo: The configuration table should be ignored\n");
    }

// Features
// Few feature bytes.
// If bit 7 is set 
// then the IMCR is present and PIC mode is being used, 
// otherwise virtual wire mode is. 
// All other bits are reserved.
    printf("Features: {%d}\n", MPTable->features);
// Se o bit 7 está ligado.
    if ( MPTable->features & (1 << 7) ){
         printf("The IMCR is present and PIC mode is being used.\n");
    }
// Se o bit 7 está desligado.
    if ( (MPTable->features & (1 << 7)) == 0 ){
         printf("Using the virtual wire mode.\n");
    }

    //#debug
    //refresh_screen();
    //while(1){}

// ==============================================
// MPConfigurationTable structure.
// Pointed by th MP Floating point structure.

// Struture pointer.
// MP Configuration table.
    MPConfigurationTable = 
        (struct mp_configuration_table_d *) configurationtable_address;

    if ((void*) MPConfigurationTable == NULL ){
        printf("x64_probe_smp: Invalid Configuration table address\n");
        goto fail;
    }
// Saving
    smp_info.mp_configuration_table = 
        (struct mp_configuration_table_d *) MPConfigurationTable;


// Signature
// "PCMP"
    printf("Signature: %c %c %c %c\n",
        MPConfigurationTable->signature[0],
        MPConfigurationTable->signature[1],
        MPConfigurationTable->signature[2],
        MPConfigurationTable->signature[3] );


// Intel strings: 
// "OEM00000" "PROD00000000"

// OEM ID STRING
    char oemid_string[8+1];
    for (i=0; i<8; i++){
        oemid_string[i] = MPConfigurationTable->oem_id[i];
    };
    oemid_string[8]=0;  // finish
    printf("OEM ID STRING: {%s}\n",oemid_string);

// PRODUCT ID STRING
    char productid_string[12+1];
    for (i=0; i<12; i++){
        productid_string[i] = MPConfigurationTable->product_id[i];
    };
    productid_string[12]=0;  // finish
    printf("PRODUCT ID STRING: {%s}\n",productid_string);

// Lapic address
    printf("lapic address: {%x}\n",
        MPConfigurationTable->lapic_address );

// Is this the standard lapic address?
    if ( MPConfigurationTable->lapic_address != LAPIC_BASE )
    {
        printf("fail: Not standard lapic address\n");
        printf("Found={%x} Standard{%x}\n",
            MPConfigurationTable->lapic_address,
            LAPIC_BASE );
    }

//
// Entries
//

// Probing the entries right below the MPConfigurationTable.

// -------------------------------
// Max number of entries.

    register int EntryCount = 
        (int) MPConfigurationTable->entry_count;

    printf("Entry count: {%d}\n",
        MPConfigurationTable->entry_count);

    //#debug
    //refresh_screen();
    //while(1){};


// #bugbug
// Talvez essas entradas estão erradas.
// Talvez não haja entrada alguma nesse endereço aqui.


// =======================================================
// Entries
// ACPI processor, Local APIC.

// Logo abaixo da configuration table.
// começa uma sequência de entradas de tamanhos diferentes.
// Se a entrada for para descrever um processador, então 
// a entrada tem 20 bytes, caso contrario tem 8 bytes.
// see: mp.h

// The address of the first entry.
    unsigned long entry_base = 
    (unsigned long) ( configurationtable_address + 
                      sizeof( struct mp_configuration_table_d ) );


/*
entry info:
Description | Type | Length | Comments
Processor  |     0 |     20 | One entry per processor.
Bus        |     1 |      8 | One entry per bus.
I/O APIC   |     2 |      8 | One entry per I/O APIC. :)
I/O 
Interrupt 
Assignment |     3 |      8 | One entry per bus interrupt source.
Local 
Interrupt 
Assignment |     4 |      8 | One entry per system interrupt source.
*/

// #remember:
// One type of entry is IOAPIC.

// Estrutura para entradas que descrevem um processador.
// Processor = type 0.

    struct entry_processor_d *e;

// This routine gets the number of processors.
// #todo:
// We can create a method for that routine.
// Register this number into the global data.
    unsigned int NumberOfProcessors=0;
    g_processor_count = NumberOfProcessors;

// EntryCount has the max number of entries.
// #bugbug
// #test

    if ( EntryCount > 32 )
    {
        printf("#bugbug: EntryCount > 32\n");
        EntryCount = 32;
    }


// Clean the list.
    for (i=0; i<32; i++){
        smp_info.processors[i] = 0;
    };
    smp_info.number_of_processors = 0;

// loop:
// Check all the n entries indicated in the table above.
    for (i=0; i<EntryCount; i++)
    {
        // Tracing
        //printf("\n");
        //printf(":::: Entry %d:\n",i);
        
        // Looking for processors.
        e = (struct entry_processor_d *) entry_base;

        // It is a processor entry.
        if (e->type == 0){

            smp_info.processors[NumberOfProcessors] = (unsigned long) e;
            NumberOfProcessors += 1;

            // #todo
            // We neet a worker function for this job.
            printf (">>>>> PROCESSOR found! in entry %d\n",i);
            // apic id.
            printf("local_apic_id %d\n", e->local_apic_id);
            // apic version
            printf("local_apic_version %d\n", e->local_apic_version);
            // Flags:
            // If bit 0 is clear then the processor must be ignored.
            // If bit 1 is set then the processor is the bootstrap processor.
            // Ignore the processor.
            if( (e->flags & (1<<0)) == 0 ){
                printf("Processor must be ignored\n");
            }
            // BSP processor.
            if( e->flags & (1<<1) ){
                printf("x64_probe_smp: The processor is a BSP\n");
            }
            printf ("stepping: %d\n", (e->signature & 0x00F));
            printf ("   model: %d\n",((e->signature & 0x0F0) >> 4) );
            printf ("  family: %d\n",((e->signature & 0xF00) >> 8) );

            entry_base = (unsigned long) (entry_base + 20);

        // Not a processor.
        } else if (e->type != 0){
            //printf ("Device type %d in entry %d\n", e->type, i );
            entry_base = (unsigned long) (entry_base + 8);
        }
    };

done:

// Global number of processors.
    g_processor_count = 
        (unsigned int) NumberOfProcessors;

// smp number of processors.
    smp_info.number_of_processors = 
        (unsigned int) NumberOfProcessors;

// #debug
    printf("Processor count: {%d}\n",
        smp_info.number_of_processors );

// smp done.
    smp_info.initialized = TRUE;
    printf("x64_probe_smp: done\n");

    // #debug
    //refresh_screen();
    //while(1){
    //};

    // g_smp_initialized = TRUE;
    return TRUE;
fail:
    g_smp_initialized = FALSE;
    smp_info.initialized = FALSE;
    return FALSE;
}

static int __x64_probe_smp_via_acpi(void)
{
// After you've gathered the information, 
// you'll need to disable the PIC and prepare for I/O APIC. 
// You also need to setup BSP's local APIC. 
// Then, startup the APs using SIPIs.

// #todo
// Probe the acpi table.
// + 'RSDP signature'

    lapic_initializing(0xFEE00000);

    if (LAPIC.initialized == TRUE){
        printf("x64_probe_smp_via_acpi: lapic initialization ok\n");
        return TRUE;
    }else if (LAPIC.initialized != TRUE){
        printf("x64_probe_smp_via_acpi: lapic initialization fail\n");
        return FALSE;
    };

    return FALSE;
}

int x64_initialize_smp(void)
{
// Called I_kmain() in main.c
// Probing if smp is supported.
// + Via MP.
// + Via ACPI.

    int smp_status = FALSE;  // fail

//
// The SMP support.
//

    PROGRESS("x64_initialize_smp:\n");

    // #debug
    //printf("\n");
    //printf("---- SMP START ----\n");
    printf("x64_initialize_smp:\n");

// Initialize smp support via MP Floating point structure. (kinda).
// Testando a inicializaçao do lapic.
// Tentando ler o id e a versao.
// It works on qemu and qemu/kvm.
// It doesn't work on Virtualbox. (Table not found).
// See: x64.c

    smp_status = (int) __x64_probe_smp();

    if (smp_status == TRUE)
    {
        printf("x64_initialize_smp: [x64_probe_smp] ok\n");
        // Initialize LAPIC based on the address we found before.
        if ((void*) MPConfigurationTable != NULL)
        {
            if (MPConfigurationTable->lapic_address != 0)
            {
                // see: apic.c
                lapic_initializing( MPConfigurationTable->lapic_address );
                if (LAPIC.initialized == TRUE){
                    printf("??: lapic initialization ok\n");
                }else if (LAPIC.initialized != TRUE){
                    printf("??: lapic initialization fail\n");
                };
            }
        }
    }

    if (smp_status != TRUE)
    {
        printf("x64_initialize_smp: [x64_probe_smp] fail\n");
        // #test #todo
        // Using the ACPI tables.
        smp_status = (int) __x64_probe_smp_via_acpi();
        if (smp_status != TRUE){
            printf("x64_initialize_smp: [x64_probe_smp_via_acpi] fail\n");
        }
    }

    //#debug
    //printf("smp: #breakpoint\n");
    //refresh_screen();
    //while(1){}

    //printf("---- SMP END ----\n");
    //printf("\n");
    
    return (int) smp_status;
}



/*
// #todo
void x64_show_smp_into(void);
void x64_show_smp_into(void)
{
// Processor entry.
    struct entry_processor_d *p_entry;
    int i=0;

    if (smp_info.initialized != TRUE)
        return;
    // #debug
    if (smp_info.number_of_processors > 16)
        return;

    for (i=0; i<smp_info.number_of_processors; i++)
    {
        p_entry = (struct entry_processor_d *) smp_info.processors[i];
        if ( (void*) p_entry != NULL )
        {
            //#todo
            // Print info.
        }
    };
}
*/

