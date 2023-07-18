
#include "crt0.hpp"


#define NULL  ( (void*) 0 )

// crt0 file for a ring0 kernel module.

extern int main( int arc, char *argv[], int reason );

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
void module_crt0(int reason)
{
    int ret_val=0;

// Calling the main function.
// IN: 
// reason

    ret_val = (int) main(2,crt0_args,reason);

// Return to kernel
    //while(1){};
}


