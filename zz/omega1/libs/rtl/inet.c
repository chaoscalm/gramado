

#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <rtl/gramado.h> 



// Not tested
uint32_t htonl(uint32_t hostlong)
{
    return (uint32_t) (((hostlong >> 24) & 0xFF) | 
                       ((hostlong << 8)  & 0xFF0000) | 
                       ((hostlong >> 8)  & 0xFF00) | 
                       ((hostlong << 24) & 0xFF000000));
}

// Not tested
uint16_t htons(uint16_t hostshort)
{
    return (uint16_t) ((hostshort >> 8) | (hostshort << 8));
}


// Not tested
uint32_t ntohl(uint32_t netlong)
{
    return (uint32_t) (((netlong >> 24) & 0xFF) | 
                       ((netlong << 8)  & 0xFF0000) | 
                       ((netlong >> 8)  & 0xFF00) | 
                       ((netlong << 24) & 0xFF000000));
}

// Not tested
uint16_t ntohs(uint16_t netshort)
{
    return (uint16_t) ((netshort >> 8) | (netshort << 8));
}


/*
//not tested
uint16_t ____htons (uint16_t  w)
{ 
    return (w & 0xff) << 8 | ((w >> 8) & 0xff); 
}
*/


/*
//not tested
uint16_t ____ntohs (uint16_t  w)
{ 
    return (w & 0xff) << 8 | ((w >> 8) & 0xff); 
}
*/








