
// bitblt.c
// Bit-block Transfer.

#include "../gwsint.h"


// see: 
// rect.c for methods with rectangles.
int 
bitblt0(
    struct gws_rect_d *dst_rect,
    struct gws_rect_d *src_rect,
    unsigned long rop,
    int op )
{

    if ( (void*) src_rect == NULL ){
        return -1;
    }

// Simple transfer to lfb
    if (op == BITBLT_OP_COPY_TO_LFB)
    {
        src_rect->dirty = TRUE;
        gwssrv_refresh_this_rect(src_rect);
        return TRUE;
    }

// Copy from src to dst
    if (op == BITBLT_OP_COPY_TO_DST)
    {
        //#todo
        return TRUE;
    }

// ...

    return FALSE;
}

// see: 
// rect.c for methods with rectangles.
int 
bitblt(
    struct gws_rect_d *src_rect,
    unsigned long rop,
    int op )
{

    if ( (void*) src_rect == NULL ){
        return -1;
    }

// Simple transfer to lfb
    if (op == BITBLT_OP_COPY_TO_LFB)
    {
        src_rect->dirty = TRUE;
        gwssrv_refresh_this_rect(src_rect);
        return TRUE;
    }
 

    return FALSE;
}


    
