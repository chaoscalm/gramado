
// schedq.c

#include <kernel.h>

unsigned long sched_queues[SCHEQ_COUNT_MAX];

// Global queue.
// The current list
struct thread_d  *currentq;



