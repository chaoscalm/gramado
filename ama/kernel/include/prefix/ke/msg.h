
// msg.h

#ifndef __PS_MSG_H
#define __PS_MSG_H    1

// -----------------------------------------------------
// Message structure.
struct msg_d 
{

// -----------------------
// validation
    int used;
    int magic;

// -----------------------
// Standard header
    void *opaque_window;
    int msg;
    unsigned long long1;
    unsigned long long2;
// -----------------------
// Extra payload
    unsigned long long3;
    unsigned long long4;

// -----------------------
// Identification field
    tid_t sender_tid;
    tid_t receiver_tid;
    pid_t sender_pid;
    pid_t receiver_pid;

// -----------------------
// Navigation
    struct msg_d *next;
};

// --------------------------------------

int
post_message_to_tid2 ( 
    tid_t sender_tid,
    tid_t receiver_tid,
    int msg, 
    unsigned long long1, 
    unsigned long long2,
    unsigned long long3,
    unsigned long long4 );

int
post_message_to_tid ( 
    tid_t sender_tid,
    tid_t receiver_tid,
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

// Service 112
unsigned long
sys_post_message_to_tid( 
    int tid, 
    unsigned long message_buffer );

int
post_message_to_foreground_thread ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

int
post_message_to_init ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );
 
int
post_message_to_ws( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

int 
cali_post( 
    tid_t sender_tid,
    tid_t receiver_tid,
    struct msg_d *message );

// ----------

// Service 111.
// Get a message from the current thread and 
// put it into the given buffer.
// The message has 6 standard elements.
// See: thread.c
void *sys_get_message(unsigned long ubuf);
void *sys_get_message2(unsigned long ubuf, int index, int restart);


#endif    




