
// schedq.h

#ifndef __SCHEDQ_H
#define __SCHEDQ_H    1

// The index for the head of the current queue.
#define SCHED_CURRENT_QUEUE  0
// Normal priorities
#define SCHED_P1_QUEUE  1
#define SCHED_P2_QUEUE  2
#define SCHED_P3_QUEUE  3
// System priorities
#define SCHED_P4_QUEUE  4
#define SCHED_P5_QUEUE  5
#define SCHED_P6_QUEUE  6
// Max number of elements.
#define SCHEQ_COUNT_MAX  7

// see: schedq.c
extern unsigned long sched_queues[SCHEQ_COUNT_MAX];

// Global queue.
// The current list
extern struct thread_d  *currentq;

#endif    


