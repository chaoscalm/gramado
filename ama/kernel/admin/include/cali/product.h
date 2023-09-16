

// product.h
// Project California.

#ifndef __CALI_PRODUCT_H
#define __CALI_PRODUCT_H    1

#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...


//
// Plataform support.
//

//environment variables.
#define PLATFORM_PATH  "/Platform"
#define HARDWARE_PATH  "/Platform/Hardware"
#define FIRMWARE_PATH  "/Platform/Firmware"
#define SYSTEM_PATH    "/Platform/System"
//#define USERS_PATH     "/Platform/Users"
//...


// ------------------------------
// Product type.
typedef enum {
    PT_UNDEFINED,
    PT_THINGS,          // Things.
    PT_EDGEDEVICES,     // Edge Devices.
    //PT_COREDEVICES,   // Core Devices. (haha)
}ProductType_t;
//Type of product.
extern int g_product_type; 


// ------------------------------
// Platform type.
typedef enum {
   PFT_16BIT,       //16bit processor.
   PFT_32BIT,       //32bit processor.
   PFT_64BIT,       //64bit processor.
   //...
}PlatformType_t;
//size of processor word.
extern int g_platform_type;



// ------------------------------
// UP ou MP
typedef enum {
    SYSTEM_TYPE_NULL,
    SYSTEM_TYPE_UNIPROCESSOR,
    SYSTEM_TYPE_MULTIPROCESSOR
} SystemType_t;
extern int g_system_type;



#endif   


