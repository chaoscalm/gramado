
// newm0.h

#ifndef __NEWM0_H
#define __NEWM0_H  1

#include "klimits.h"
#include "ktypes.h"
#include "ktypes2.h"
#include "kstddef.h"
#include "kstdarg.h"
#include "ports64.h"

struct module_initialization_d
{
    int initialized;
    //unsigned long ksysmboltable_address;
};
extern struct module_initialization_d  ModuleInitialization;


struct display_info_d
{
    int initialized;

    // Initialization phase 1.
    int phase1;
    unsigned long frontbuffer_address;
    unsigned long backbuffer_address;

    // Initialization phase 2.
    int phase2;
    unsigned long width;
    unsigned long height;
    unsigned long bpp;   // bits per pixel.

    // ...
};
extern struct display_info_d DisplayInfo;







#endif  


