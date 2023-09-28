
// mmsize.h
// memory size support.

#ifndef __MM_MMSIZE_H
#define __MM_MMSIZE_H    1

// Size support.
#define KB  (1024)
#define MB  (1024 * 1024)
#define GB  (1024 * 1024 * 1024)


#define __SMALL   ( 256 -1)
#define __MEDIUM  ( 512 -1)
#define __LARGE   (1024 -1)

// --------------
// Tamanho dado em bytes.
#define SMALLSYSTEM_SIZE  ( __SMALL  *1024*1024)
#define MEDIUMSYSTEM_SIZE ( __MEDIUM *1024*1024)
#define LARGESYSTEM_SIZE  ( __LARGE  *1024*1024)

// Tamanho do sistema, dado em KB.
#define SMALLSYSTEM_SIZE_KB  (__SMALL  * 1024)
#define MEDIUMSYSTEM_SIZE_KB (__MEDIUM * 1024)
#define LARGESYSTEM_SIZE_KB  (__LARGE  * 1024)

// #todo
// Tamanho do sistema, dado em MB.
#define SMALLSYSTEM_SIZE_MB  (__SMALL)
#define MEDIUMSYSTEM_SIZE_MB (__MEDIUM)
#define LARGESYSTEM_SIZE_MB  (__LARGE)

// Tamanho so sitema, dado em quantidade de páginas de 4KB.
#define SMALLSYSTEM_SIZE_PAGES  ( (__SMALL  *1024*1024) / 4096 )
#define MEDIUMSYSTEM_SIZE_PAGES ( (__MEDIUM *1024*1024) / 4096 )
#define LARGESYSTEM_SIZE_PAGES  ( (__LARGE  *1024*1024) / 4096 )
// --------------



//
// Memory size support.
//

//base     = base memory retornada pelo cmos
//other    = (1MB - base). (Shadow memory = 384 KB)
//extended = retornada pelo cmos.
//total    = base + other + extended.
// alias
extern unsigned long memorysizeBaseMemoryViaCMOS;

extern unsigned long memorysizeBaseMemory;
extern unsigned long memorysizeOtherMemory;
extern unsigned long memorysizeExtendedMemory;
extern unsigned long memorysizeTotal;

extern unsigned long memorysizeInstalledPhysicalMemory;
extern unsigned long memorysizeTotalPhysicalMemory;
extern unsigned long memorysizeAvailablePhysicalMemory;
// Used
extern unsigned long memorysizeUsed;
// Free
extern unsigned long memorysizeFree;



//
// System memory type.
//

// Tipo de sistema baseado no tamanho da memoria.
typedef enum {
    stNull,
    stSmallSystem,
    stMediumSystem,
    stLargeSystem,
}mm_system_type_t;

// Salva o tipo de sistema baseado no tamanho da memória.
// see: mm.c
extern int g_mm_system_type;



struct memory_size_info_d
{

// If this structure was initialized or not.
// Initialized by mmsize_initialize() in mmsize.c
    int initialized;

    // ...

};
// see: mmsize.c
extern struct memory_size_info_d MemorySizeInfo;

// ==========================

int mmsize_initialize(void);

#endif   

