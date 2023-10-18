// x64cont.h
// x86_64 context support.

#ifndef __X64COUNT_H
#define __X64COUNT_H    1

// #todo
// functions to 'save' and 'restore' context.


struct x64_context_d
{

//-------------------------------
// General Purpose Registers. (GPRs).
    // Historical reason.
    unsigned long rax;
    unsigned long rbx;
    unsigned long rcx;
    unsigned long rdx;
    unsigned long rbp;
    unsigned long rsi;
    unsigned long rdi;
    unsigned long rsp;
    // New ones.
    unsigned long r8;
    unsigned long r9;
    unsigned long r10;
    unsigned long r11;
    unsigned long r12;
    unsigned long r13;
    unsigned long r14;
    unsigned long r15;

//-------------------------------
// Program counter (PC), 
// commonly called the instruction pointer (IP).
    unsigned long rip;

//-------------------------------
// Flags
    unsigned long rflags;

//-------------------------------
// Segment registers
    unsigned short cs;
    unsigned short ds;
    unsigned short es;
    unsigned short fs;
    unsigned short gs;
    unsigned short ss;

//-------------------------------
// FPU
// #todo
// 512 bytes, alinhados em 16.
// unsigned char fxsave[512]__atribute_aligned(...);
    unsigned char fpu_buffer[512];
};


//
// == prototypes ==============
//

void save_current_context (void);
void restore_current_context (void);
int contextCheckThreadRing3Context (int tid);

#endif    


