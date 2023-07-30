
// host.h

#ifndef __OS_HOST_H
#define __OS_HOST_H    1

struct gws_host_d
{
    int id;
    int used;
    int magic;

// #todo: Waste of memory.
    char name[256];
    // ...
};

#endif    



