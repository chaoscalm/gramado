
// msgloop.c

#include "init.h"

#define __MSG_CLOSE     7
#define __MSG_COMMAND  40

static char __filename_local_buffer[64];

// The tid of the caller.
// Sent us a system message.
struct endpoint_d  Caller;

struct next_msg_d
{

// tid
    int target_tid;

// Message
    int msg_code;
    unsigned long long1;
    unsigned long long2;
};
struct next_msg_d  NextMessage;

static int NoReply = TRUE;

//-----------------------------------------

static void __send_response(void);

static int __idlethread_loop(void);
static void do_hello(int src_tid);
static void do_reboot(int src_tid);

// local
static int 
processEvent ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2,
    int caller_tid );

// ===========================

// #test Hello.
// Responding the hello.
// Hey init, are you up?
static void do_hello(int src_tid)
{
    int dst_tid = src_tid;

    //printf("init.bin: 44888 received | sender=%d receiver=%d\n",
    //    RTLEventBuffer[8],   //sender (the caller)
    //    RTLEventBuffer[9] ); //receiver

    printf("init.bin: [44888] Hello received from %d\n", 
        src_tid );

    if (dst_tid<0)
        return;

//
// Reply
//

// -------------
// Reply: 
// Sending response
// Sending back the same message found into the buffer.
// Message back to caller.

// The message buffer address.
    unsigned long msg_buffer_address = 
        (unsigned long) RTLEventBuffer;

    rtl_post_system_message( 
        (int) dst_tid,
        (unsigned long) msg_buffer_address );

/*
// #test
// It's working!
    NextMessage.target_tid = (int) dst_tid;
    NextMessage.msg_code = __MSG_CLOSE; // HEHE
    NextMessage.long1 = 0;
    NextMessage.long2 = 0;
    NoReply = FALSE;
*/
}

static void do_reboot(int src_tid)
{

// Invalid tid
    if (src_tid < 0)
        return;

// Not the kernel.
    if (src_tid != 99)
        return;

    printf("init.bin: [55888] reboot request from %d\n", 
        src_tid );
    rtl_reboot();
}

// local
// #todo: change this name.
static int 
processEvent ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2,
    int caller_tid )
{
// Processing requests.

// Invalid message code.
    if (msg<0){
        return -1;
    }

// Invalid caller.
// #todo: 
// End if the kernel is sending us a system message?
    //if (caller_tid)
        //return -1;

    switch (msg){

// Start a client.
// It's gonna wor only if the is already running.
// range: 4001~4009 

    case __MSG_COMMAND:
        //printf("init.bin: MSG_COMMAND %d \n",long1);
        switch (long1)
        {
            // #bugbug
            // There is something wrong with the filename strings
            // when calling the launcher rtl_clone_and_execute("?").
            // #todo: We need a good local buffer for the string.
            case 4001:  //app1
                // This is a special tid used by the kernel.
                // This thread doesn't exist.
                if (caller_tid != 99){
                    break;
                }
                printf("init.bin: 4001, from {%d}\n",caller_tid);
                memset(__filename_local_buffer,0,64);
                sprintf(__filename_local_buffer,"terminal.bin");
                rtl_clone_and_execute(__filename_local_buffer);
                break;
            case 4002:  //app2
                // This is a special tid used by the kernel.
                // This thread doesn't exist.
                if (caller_tid != 99){
                    break;
                }
                printf("init.bin: 4002\n");
                break;
            case 4003:  //app3
                // This is a special tid used by the kernel.
                // This thread doesn't exist.
                if (caller_tid != 99){
                    break;
                }
                //printf("init.bin: 4003\n");
                break;
            case 4004:  //app4
                // This is a special tid used by the kernel.
                // This thread doesn't exist.
                if (caller_tid != 99){
                    break;
                }
                //printf("init.bin: 4004\n");
                break;
            // ...
            default:
                break;
        };
        break;

// 'Hello' received. Let's respond.
    case 44888:
        do_hello(caller_tid);
        break;

// Reboot receive.
// #warning
// Who can send us this message?
    case 55888:
        // Not the kernel
        if (caller_tid != 99)
            break;
        do_reboot(caller_tid);
        break;

    // #todo
    //case MSG_YIELD:
        //rtl_yield();
        //break;

// #warning
// Who can send us this message?

    case __MSG_CLOSE:
        // Not the kernel
        if (caller_tid != 99)
            break;
        printf("#debug: Sorry, can't close init.bin\n");
        break;

    // ...

    default:
        break;
    };
    
    return 0;
}


static void __send_response(void)
{
    if (NoReply == TRUE)
        return;

// Post next response.

    RTLEventBuffer[0] = 0;
    RTLEventBuffer[1] = (unsigned long) (NextMessage.msg_code & 0xFFFFFFFF);
    RTLEventBuffer[2] = (unsigned long) NextMessage.long1;
    RTLEventBuffer[3] = (unsigned long) NextMessage.long2;

    rtl_post_system_message( 
        (int) NextMessage.target_tid,
        (unsigned long) RTLEventBuffer );

// Clear message
    NextMessage.target_tid = 0;
    NextMessage.msg_code = 0;
    NextMessage.long1 = 0;
    NextMessage.long2 = 0;
    NoReply = TRUE;   // No more responses.
}

static int __idlethread_loop(void)
{
// Get input from idlethread.
// Getting requests or events.

    NoReply = TRUE;

// #todo
// Get the id of the caller.
// Get the message code.
// Who can call us?

// Nessa hora ja não nos preocupamos mais com essa thread.
// Ele receberá algumas mensagens eventualmente.
    while (TRUE){
        //if( isTimeToQuit == TRUE )
            //break;
        if ( rtl_get_event() == TRUE )
        {
            // Get caller's tid.
            Caller.tid = (int) ( RTLEventBuffer[8] & 0xFFFF );
            // Dispatch.
            processEvent ( 
                (void*) RTLEventBuffer[0], 
                RTLEventBuffer[1],  // msg 
                RTLEventBuffer[2], 
                RTLEventBuffer[3],
                Caller.tid );
            //#test
            //rtl_yield();
            Caller.tid = -1;
        }

        if (NoReply == FALSE){
            __send_response();
        }
    };

    return 0;
}

// We're not using the unix-sockets
// just like in a regular Gramado server. 
// We're just getting messages in the threads message queue.
int run_server(void)
{
    int IdleLoopStatus = -1;

    printf("init.bin: Running in server mode\n");

    Caller.tid = -1;
    Caller.initialized = TRUE;

    //# no focus!
    //rtl_focus_on_this_thread();
    IdleLoopStatus = (int) __idlethread_loop();
    if (IdleLoopStatus<0){
        printf ("init.bin: loop fail\n");
    }
    return 0;
}

