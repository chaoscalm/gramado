/*
 * File: limits.h 
 *     It defines some limits in the libc.
 *     ring 0.
 *     2005 - Created by Fred Nora.
 */

#ifndef ____LIMITS_H
#define ____LIMITS_H    1

// Max number of open files in a process.
#define OPEN_MAX  GRAMADO_FOPEN_MAX

#define PIPE_BUF  GRAMADO_PIPE_BUF

// Number of bits in a 'char'.  
#define CHAR_BIT  8
//#todo: Use default lib.
#define HEX_LEN  8

//
// CHAR
//


// Minimum and maximum values a 'signed char' can hold.  
// 0x80 0x7f
#define SCHAR_MIN  (-128)
#define SCHAR_MAX  127
// Maximum value an 'unsigned char' can hold.  (Minimum is 0.)  
// 0xff
#define UCHAR_MAX  255

//
// SHORT
//

// Minimum and maximum values a 'signed short int' can hold.  
// 0x8000  0x7fff
#define SHRT_MIN  (-32768)
#define SHRT_MAX  32767 
// Maximum value an 'unsigned short int' can hold.  (Minimum is 0.) 
// 0xffff
#define USHRT_MAX  65535

//
//  INT
//

// 0x80000000
// #define ____INT_MIN  ?
// 0x7fffffff
#define ____INT_MAX  2147483647



#endif    





