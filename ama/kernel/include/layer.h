
// layer.h

#ifndef __ZCALL_LAYER_H
#define __ZCALL_LAYER_H    1


#define LAYER_UNDEFINED  0

// ---------------------
// Kernel modules
// #define LAYER_AA  1  //mod0.bin

// ---------------------
#define LAYER_AMA  10   //kernel.bin
// alias
#define LAYER_KERNEL  LAYER_AMA

// ---------------------
#define LAYER_ZING_L1  100  // init
#define LAYER_ZING_L2  200  // gramland
#define LAYER_ZING_L3  300  // network server

// alias
#define LAYER_INIT            LAYER_ZING_L1
#define LAYER_GRAMLAND        LAYER_ZING_L2
#define LAYER_NETWORK_SERVER  LAYER_ZING_L3

// ---------------------


#define __LAYER_ZZ_OMEGA2_DRIVERS   1000  // drivers
#define __LAYER_ZZ_OMEGA2_SERVERS   2000  // servers
#define __LAYER_ZZ_OMEGA3_COMMANDS  3000  // commands
#define __LAYER_ZZ_OMEGA4_APPS      4000  // apps

// Aliases
#define LAYER_ZZ_L1  __LAYER_ZZ_OMEGA2_DRIVERS
#define LAYER_ZZ_L2  __LAYER_ZZ_OMEGA2_SERVERS
#define LAYER_ZZ_L3  __LAYER_ZZ_OMEGA3_COMMANDS
#define LAYER_ZZ_L4  __LAYER_ZZ_OMEGA4_APPS

// Aliases
#define LAYER_DRIVER   LAYER_ZZ_L1
#define LAYER_SERVER   LAYER_ZZ_L2
#define LAYER_COMMAND  LAYER_ZZ_L3
#define LAYER_APP      LAYER_ZZ_L4

#endif  

