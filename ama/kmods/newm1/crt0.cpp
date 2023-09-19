
#include "crt0.hpp"

#define NULL  ((void*) 0)

// crt0 file for a ring0 kernel module.

extern unsigned long 
module_main (
    unsigned long arg1,
    unsigned long arg2,
    unsigned long arg3,
    unsigned long arg4 );

/*
const char *crt0_args[] = {
    "one",
    "two",
    NULL
};
*/
char *crt0_args[] = {
    "one",
    "two",
    (char *) 0  //NULL
};


// Entry point
unsigned long  
module_crt0(
    unsigned long rdi_reason,
    unsigned long rsi_long1,
    unsigned long l3,
    unsigned long l4 )
{
    //unsigned long reason = (unsigned long) rdi_reason;
    //unsigned long long1  = (unsigned long) rsi_long1;
    //int ret_val=0;

    unsigned long arg1 = (unsigned long) rdi_reason;
    unsigned long arg2 = (unsigned long) rsi_long1;   
    unsigned long arg3 = (unsigned long) l3; 
    unsigned long arg4 = (unsigned long) l4; 
    unsigned long return_value=0;

// Calling the main function.
// IN: 
// reason

    // #todo
    // The return value needs to be long
    //ret_val = (int) main(2,crt0_args,reason);
    return_value = 
        (unsigned long) module_main(arg1,arg2,arg3,arg4);

// Return to kernel
    //while(1){};

    return (unsigned long) 1234;
}



