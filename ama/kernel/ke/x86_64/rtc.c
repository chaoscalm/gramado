
// rtc.c

#include <kernel.h>  

struct rtc_d  *rtc;

static void DeviceInterface_RTC(void);
int __rtc_init_datastructure(void);


// ===========================


// read_cmos_bcd:
// Lê da CMOS um determinado registro. 
// IN:
// #todo: 
// Use a type in this parameter.

unsigned long read_cmos_bcd (unsigned reg)
{
// 64bit
    unsigned long Result=0;
// 32bit
    unsigned int high_digit=0; 
    unsigned int low_digit=0;

    out8 ( 0x70, ( in8(0x70) & 0x80) | (reg & 0x7F) );
    high_digit = low_digit = in8(0x71);

// Converte BCD para binário. 
    high_digit >>= 4;

    high_digit &= 0x0F;
    low_digit  &= 0x0F;

    Result = (unsigned long) (10*high_digit) + low_digit;

    Result = (unsigned long) Result & 0x00000000FFFFFFFF;

    return (unsigned long) Result;
}

/*
 * get_date: 
 * Pega a data armazenada na CMOS. 
 * Formato(bytes): YYMD 
 * todo: 
 * Essa função pode ser trabalhada sem riscos ao sistema.
 */
unsigned long get_date(void)
{
    unsigned long date=0;

    date  = read_cmos_bcd(9);
    date += read_cmos_bcd(8) * 31;
    date += read_cmos_bcd(7) * (31*12);

    return (unsigned long) date;
}

/*
 * get_time:
 * Pega o horário armazenado na CMOS.
 * Formato: Cada unidade representa 1 segundo. 
 * todo: Essa função pode ser trabalhada sem riscos ao sistema.
 * STATUS: Não funciona muito bem. @todo: rever isso
 * Obs: 
 * Na verdade pode estar funcionando e o relógio da máquina virtual
 * está desatualizado.
 */
unsigned long get_time(void)
{
    unsigned long time=0;

    time  = read_cmos_bcd(0);
    time += read_cmos_bcd(2) * 60;
    time += read_cmos_bcd(4) * (60*60);

    return (unsigned long) time;
}

/* 
 * rtcGetBaseMemory:
 *     Get base memory info via CMOS. 
 *  15h		Low byte of base memory size
 *				100h = 256k
 *				200h = 512k
 *				280h = 640k
 *	16h		High byte of 15h above
 *	17h		Low expansion memory byte
 *	18h		High expansion memory byte
 *				200h = 512k
 *				400h = 1024k
 *				600h-3C00h = 1536-15,360k
 *	19h		Extended type byte: Hard drive 1
 *	1Ah		Extended type byte: Hard drive 2
 *	1Bh-2Dh		reserved
 *	2Eh		check-sum for addresses 10h-2Dh  (word)
 *	2Fh		  see above
 *	30h		Low expansion memory byte
 *	31h		High expansion memory byte
 *				200h = 512k
 *				400h = 1024k
 *				600h-3C00h = 1536-15,360k
 *	Limite de uma 'word'??
 */
unsigned short rtcGetBaseMemory (void)
{
    unsigned short total = 0;
    unsigned char lowmem=0;
    unsigned char highmem=0;

// Low. (Low base memory byte)
    out8(0x70, RTC_LOWBYTE_BASEMEMORY);
    lowmem = in8(0x71);
// High. (High base memory byte)
    out8(0x70, RTC_HIGHBYTE_BASEMEMORY);
    highmem = in8(0x71);
// Total.
// #bugbug 
// #todo: Write a better code here.
    total = lowmem | highmem << 8;

    return (unsigned short) total;
}


/*
 * rtcGetExtendedMemory:
 *     Get total memory info via CMOS. 
 *
 *  15h		Low byte of base memory size
 *				100h = 256k
 *				200h = 512k
 *				280h = 640k
 *	16h		High byte of 15h above
 *	17h		Low expansion memory byte
 *	18h		High expansion memory byte
 *				200h = 512k
 *				400h = 1024k
 *				600h-3C00h = 1536-15,360k
 *	19h		Extended type byte: Hard drive 1
 *	1Ah		Extended type byte: Hard drive 2
 *	1Bh-2Dh		reserved
 *	2Eh		check-sum for addresses 10h-2Dh  (word)
 *	2Fh		  see above
 *	30h		Low expansion memory byte
 *	31h		High expansion memory byte
 *				200h = 512k
 *				400h = 1024k
 *				600h-3C00h = 1536-15,360k
 *	
 *	Limite de uma 'word' ??
 */

unsigned short rtcGetExtendedMemory(void)
{
    unsigned short total = 0;
    unsigned char lowmem = 0;
    unsigned char highmem = 0;

// Low. (Low extended memory byte)
    out8 (0x70, RTC_LOWBYTE_EXTENDEDMEMORY);
    lowmem = in8(0x71);
// High. (High extended memory byte)
    out8 (0x70, RTC_HIGHBYTE_EXTENDEDMEMORY);
    highmem = in8(0x71);
// Total.
// #bugbug 
// #todo: Write a better code here.
    total = (unsigned short) lowmem | highmem << 8;
    //total = (unsigned short) lowmem | highmem << 8;

    return (unsigned short) total;
}


/*
 * __rtc_init_datastructure:
 * Essa função deve ser chamada apenas uma vez na 
 * inicialização do módulo. 
 * #todo: 
 * Criar métodos que pegam esses valores salvos na estrutura.
 */
// #bugbug
// Alocando memória toda vez que chama a função.
// Issa alocação deveria ser feita apenas uma vez
// na inicialização, depois somente atualizados os valores.

int __rtc_init_datastructure(void)
{

// Global struct
    rtc = (void *) kmalloc( sizeof(struct rtc_d) );
    if ( (void *) rtc == NULL ){
        printf ("get_cmos_info: rtc\n");
        goto fail;
    }
    rtc->used = FALSE;
// Time
    rtc->Seconds = read_cmos_bcd(0);
    rtc->Minutes = read_cmos_bcd(2);
    rtc->Hours   = read_cmos_bcd(4);
// Date
    rtc->Year = read_cmos_bcd(9);    
    rtc->Year = (2000 + rtc->Year);
    rtc->Month = read_cmos_bcd(8);    
    rtc->DayOfMonth = read_cmos_bcd(7);  
    rtc->used = TRUE;
    rtc->magic = 1234;

// #bugbug
// Pointer not initialized yet.
// Hardware structure
    //if ( (void *) Hardware == NULL )
    //{
        // #bugbug
    //    printf("get_cmos_info: Hardware\n");
    //    goto fail;
    //}
    
// Save
    //Hardware->rtc = rtc;


    //#debug
    //printf("Time=%d:%d:%d\n", rtc->Hours, rtc->Minutes, rtc->Seconds );
    //printf("Date=%d/%d/%d\n", rtc->DayOfMonth, rtc->Month, rtc->Year );
    //refresh_screen();
    //while(1){}

    return 0;

fail:
    //free(rtc);
    refresh_screen();
    return -1;
}

/*
 * init_rtc: 
 *     Inicia a data e a hora do controlador.
 * #todo: 
 *     Essa função não deveria mostrar informações na tela.
 * tem que criar função pra isso.
 * essa aqui so deveria pegar as informações e colocar em estrutura.
 */
// Called by init_executive in system.c
// CMOS
// CLOCK - Pega informações de Hora e Data.

int init_rtc(void)
{
    debug_print("init_rtc:\n");

    __breaker_rtc_initialized = FALSE;

// #todo: 
// Criar uma estrutura para RTC.
// Alocar memoria para a estrutura rtc.
// Inicializar algumas variaveis da estrutura rtc.

    __rtc_init_datastructure();

    //unsigned long Time, Date;
    //Time = get_time();
    //Date = get_date();  
    //printf("CLOCK INFORMATION:\n");
    //printf("Time=%d Date=%d\n", Time, Date);

    __breaker_rtc_initialized = TRUE;

    g_driver_rtc_initialized = TRUE;
    return 0;
}

/*
 * DeviceInterface_RTC: 
 *     irq8 interrupt handler.
 *     System CMOS, Realtime clock. 
 */
static void DeviceInterface_RTC(void)
{
    debug_print("DeviceInterface_RTC: [TODO]\n");
}

__VOID_IRQ 
irq8_RTC (void)
{
    debug_print("irq8_RTC:\n");
    DeviceInterface_RTC();
}  



