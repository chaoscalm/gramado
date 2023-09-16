
// cali.c (Hollywood stars)
// Far Far Away
// Overall wrapper.

#include <kernel.h>

void cali_reboot(void)
{
    keReboot();
}

void cali_shutdown(int how)
{
    //hal_shutdown();
    panic("cali_shutdown: #todo\n");
}

void cali_die(void)
{
    keDie();
}

void cali_spawn_thread_by_tid(tid_t tid)
{
    if (tid<0 || tid>=THREAD_COUNT_MAX)
        return;
    psSpawnThreadByTID(tid);
}




