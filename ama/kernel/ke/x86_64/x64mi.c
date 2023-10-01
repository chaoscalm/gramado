
// mi.c
// Maskable interrups
// see: sw1.asm

#include <kernel.h>


void *mi80h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    return (void*) sci0(number,arg2,arg3,arg4);
}

void *mi81h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    return (void*) sci1(number,arg2,arg3,arg4);
}

void *mi82h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    return (void*) sci2(number,arg2,arg3,arg4);
}

void *mi83h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    return (void*) sci3(number,arg2,arg3,arg4);
}


