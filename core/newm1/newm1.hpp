
// newm0.h

#ifndef __NEWM1_H
#define __NEWM1_H  1

#include "klimits.hpp"
#include "ktypes.hpp"
#include "ktypes2.hpp"
#include "kstddef.hpp"
#include "kstdarg.hpp"

struct module_initialization_d
{
    int initialized;
    //unsigned long ksysmboltable_address;
};
extern struct module_initialization_d  ModuleInitialization;

#endif  


