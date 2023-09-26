
// ioapic.c

#include <kernel.h>

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

void enable_ioapic(void)
{
// Called by I_kmain() in main.c.
    // ...
}

