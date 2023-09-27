
// ioapic.c
// Credits: Nelson cole.

#include <kernel.h>


// #todo
//#define null 0

// #todo
// I/O APIC
// see: ioapic.h
//struct __IOAPIC_REDIR_TBL ioapic_redir_table[24];

// #todo
//unsigned long ioapic_base;


//
// IO APIC Configuration 
//

/*
uint32_t cpuReadIoApic(void *ioapicaddr, uint32_t reg);
uint32_t cpuReadIoApic(void *ioapicaddr, uint32_t reg)
{
   uint32_t volatile *ioapic = (uint32_t volatile *)ioapicaddr;
   ioapic[0] = (reg & 0xff);
   return ioapic[4];
}
*/
 
/* 
void cpuWriteIoApic(void *ioapicaddr, uint32_t reg, uint32_t value); 
void cpuWriteIoApic(void *ioapicaddr, uint32_t reg, uint32_t value)
{
   uint32_t volatile *ioapic = (uint32_t volatile *)ioapicaddr;
   ioapic[0] = (reg & 0xff);
   ioapic[4] = value;
}
*/

/*
// read
unsigned int read_ioapic_register(int reg) {
	*(volatile unsigned char*)(ioapic_base + IO_APIC_IND) = reg;
	return ( *(volatile unsigned int*)(ioapic_base + IO_APIC_DAT));
}
*/

/*
// write
void write_ioapic_register(int reg, unsigned int val) {
	*(volatile unsigned char*)(ioapic_base + IO_APIC_IND) = reg;
	*(volatile unsigned int*)(ioapic_base + IO_APIC_DAT) = val;
}
*/


/*
int ioapic_masked(int n)
{
	unsigned long pointer = (unsigned long)&ioapic_redir_table;
	ioapic_redir_table[n].mask = 1;
	unsigned int *data = (unsigned int*) pointer;
	write_ioapic_register(IO_APIC_REDIR_TBL(n),*(unsigned int*)(data + (n *2)));
	return 0;
}
*/

/*
int ioapic_umasked(int n)
{
	unsigned long pointer = (unsigned long)&ioapic_redir_table;
	ioapic_redir_table[n].mask = 0;
	unsigned int *data = (unsigned int*) pointer;
	write_ioapic_register(IO_APIC_REDIR_TBL(n),*(unsigned int*)(data + (n *2)));
	return 0;
}
*/


/*
int 
set_ioapic_redir_table(
    int n,unsigned char vector,unsigned char delv_mode,
				unsigned char dest_mode,unsigned char delv_status,
				unsigned char pin_polarity,unsigned char remote_IRR,
				unsigned char trigger_mode,unsigned char mask,
				unsigned char destination)
{
	
	unsigned long pointer = (unsigned long)&ioapic_redir_table;

	unsigned int *data = (unsigned int*) pointer;

	ioapic_redir_table[n].vector 		= vector;
	ioapic_redir_table[n].delv_mode 	= delv_mode;
	ioapic_redir_table[n].dest_mode 	= dest_mode;
	ioapic_redir_table[n].delv_status	= delv_status;
	ioapic_redir_table[n].pin_polarity	= pin_polarity;
	ioapic_redir_table[n].remote_IRR	= remote_IRR;
	ioapic_redir_table[n].trigger_mode	= trigger_mode;
	ioapic_redir_table[n].mask		= mask;
	ioapic_redir_table[n].destination	= destination;

	write_ioapic_register(IO_APIC_REDIR_TBL(n),*(unsigned int*)(data + (n *2)));
	write_ioapic_register(IO_APIC_REDIR_TBL(n) + 1,*(unsigned int*)(data + (n *2) + 1));

	return 0;
}
*/

/*
int ioapic_cofiguration(int count)
{
	for(int n = 0; n < count; n++) 
	{
            if(n == 11){}
            //else
            
	        set_ioapic_redir_table(
	            n,  //IRQn
	            0x40 + n,  // vector
	            0,  // Delivery Mode
	            0,  // Destination Mode
	            0,  // RO
	            0,  // Interrupt Input Pin Polarity
	            0,  // RO
	            0,
	            1,   // /masked 
	            localId);

	}

	return 0;
}
*/

/*
int setup_ioapic()
{
	unsigned long io_apic_base_addr;

//
//  #todo  MAPEAR MAPEAR MAPEAR MAPEAR MAPEAR MAPEAR 
//

	// Mapear o IO APIC BASE
	// 0x1000 = 4KiB
	//mm_mp( IO_APIC_BASE, &io_apic_base_addr, 0x1000,0);

	ioapic_base =  io_apic_base_addr;

    // maximum redirection entry
    int count  = ((read_ioapic_register(IO_APIC_VER) >> 16) & 0xff) + 1;

	write_ioapic_register(IO_APIC_ID, localId);

	ioapic_cofiguration(count);
	
	return 0;
}
*/



void enable_ioapic(void)
{
// Called by I_kmain() in main.c.
    // ...
    //setup_ioapic()
}

