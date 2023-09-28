
// bitblt.h
// Bit-block transfer.

#ifndef __RTL_BITBLT_H
#define __RTL_BITBLT_H    1

#define BITBLT_OP_COPY_TO_LFB   0
#define BITBLT_OP_COPY_TO_LFB_AND_ROP   1
#define BITBLT_OP_COPY_TO_DST   2
#define BITBLT_OP_COPY_TO_DST_AND_ROP   3
// ...

int 
bitblt0(
    struct gws_rect_d *dst_rect,
    struct gws_rect_d *src_rect,
    unsigned long rop,
    int op );


int 
bitblt(
    struct gws_rect_d *src_rect,
    unsigned long rop,
    int op );


#endif    


