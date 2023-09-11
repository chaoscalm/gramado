
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

// Priority levels in omega2.
// Where this process lives in the stack of applications?
//L1:
// + apps         (GUI interactive)
//L2:
// + commands     (CLI interactive)
//L3:
// + drivers      (Not interactive)
//L4:
// + servers      (Not interactive)
// Omega2 application layers. 
// It affects the priority levels.
#define LAYER_ZZ_OMEGA2_L1    1000  // apps
#define LAYER_ZZ_OMEGA2_L2    2000  // commands
#define LAYER_ZZ_OMEGA2_L3    3000  // drivers
#define LAYER_ZZ_OMEGA2_L4    4000  // servers

#define LAYER_ZZ_L1  LAYER_ZZ_OMEGA2_L1
#define LAYER_ZZ_L2  LAYER_ZZ_OMEGA2_L2
#define LAYER_ZZ_L3  LAYER_ZZ_OMEGA2_L3
#define LAYER_ZZ_L4  LAYER_ZZ_OMEGA2_L4

#define LAYER_APP      LAYER_ZZ_OMEGA2_L1
#define LAYER_COMMAND  LAYER_ZZ_OMEGA2_L2
#define LAYER_DRIVER   LAYER_ZZ_OMEGA2_L3
#define LAYER_SERVER   LAYER_ZZ_OMEGA2_L4

#endif  

