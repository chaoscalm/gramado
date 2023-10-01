
#include "crt0.h"


// crt0 file for a ring0 kernel module.

extern unsigned long 
module_main (
    unsigned long param1,
    unsigned long param2,
    unsigned long param3,
    unsigned long param4 );

const char *crt0_args[] = {
    "one",
    "two",
    NULL
};

// ----------------------------------
// Entry point
unsigned long  
module_crt0(
    unsigned long l1,   // Reason.
    unsigned long l2,   // data 1
    unsigned long l3,   // data 2
    unsigned long l4 )  // data 3
{
    unsigned long param1 = (unsigned long) l1;
    unsigned long param2 = (unsigned long) l2;   
    unsigned long param3 = (unsigned long) l3; 
    unsigned long param4 = (unsigned long) l4; 
    unsigned long return_value=0;

    return_value = 
        (unsigned long) module_main( 
                            param1,
                            param2,
                            param3,
                            param4 );

    return (unsigned long) return_value;
}

