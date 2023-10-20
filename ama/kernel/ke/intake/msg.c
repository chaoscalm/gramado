
// msg.c
// Post message and get message.

#include <kernel.h>

// #todo
// #test
// Tracking the last message.
// This way we can change it in the case of repetitions.
//struct msg_d *last_msg;


int
post_message_to_tid2 ( 
    tid_t sender_tid,
    tid_t receiver_tid,
    int msg, 
    unsigned long long1, 
    unsigned long long2,
    unsigned long long3,
    unsigned long long4 )
{
// #todo:
// Nao podemos deixar que toda vez que uma thread receber uma mensagem 
// ela exija um timeout. Pois uma aplicaçao pode enviar mensagens em loop.
// Talvez isso deva ser permitido somente para mensagens de input vindas
// dos device drivers.

// Target thread.
    struct thread_d *t;
    struct msg_d *m;
    int MessageCode=0;
    // #test
    int UseTimeout=TRUE;
// TIDs
    tid_t src_tid = (tid_t) (sender_tid & 0xFFFF);
    tid_t dst_tid = (tid_t) (receiver_tid & 0xFFFF);

// Message code.
    MessageCode = (int) (msg & 0xFFFFFFFF);
    if (MessageCode<0){
        goto fail;
    }

// tid
    if ( dst_tid < 0 || dst_tid >= THREAD_COUNT_MAX ){
        panic("post_message_to_tid2: dst_tid\n");
        //goto fail;
    }
// structure
    t = (struct thread_d *) threadList[dst_tid];
    if ((void *) t == NULL){
        panic ("post_message_to_tid2: t\n");
    }
    if ( t->used != TRUE || t->magic != 1234 ){
        panic ("post_message_to_tid2: t validation\n");
    }
    if (t->tid != dst_tid){
        panic("post_message_to_tid2: t->tid != dst_tid\n");
    }

//
// This thread needs a timeout.
//

// Let's tell to ts.c that this thread needs a timeout.
// So this way the ts ca break the round and give to this thread
// the opportunity to run immediately.
// #bugbug
// A malicious process could send a lot of messages
// causing starvation in the other threads?

    if (UseTimeout==TRUE)
    {
        //if (MessageCode == MSG_KEYDOWN)
        //{
            timeout_thread = (struct thread_d *) t;
            timeout_thread->waiting_for_timeout = TRUE;
        //}
    }


//
// The message
//


// ==========================================================
// Vamos colocar essa mensagem na outra fila de mensagens.
// Essa nova fila sera a única fila no futuro.

// Get the pointer for the next entry.
    m = (struct msg_d *) t->MsgQueue[ t->MsgQueueTail ];
    if ((void*) m == NULL){
        panic ("post_message_to_tid2: m\n");
    }
    if ( m->used != TRUE || m->magic != 1234 ){
        panic ("post_message_to_tid2: m validation\n");
    }

// -------------------------
// Standard header
    m->opaque_window = NULL;
    m->msg   = (int) (MessageCode & 0xFFFFFFFF);
    m->long1 = (unsigned long) long1;
    m->long2 = (unsigned long) long2;

// -------------------------
// Extras payload
    m->long3 = (unsigned long) long3;
    m->long4 = (unsigned long) long4;

// -------------------------
// Identification field
    m->sender_tid   = (tid_t) src_tid; 
    m->receiver_tid = (tid_t) dst_tid;
    //m->sender_pid = ?;
    //m->receiver_pid = ?;

// -------------------------
    m->next = NULL;

// Done
    t->MsgQueueTail++;
    if (t->MsgQueueTail >= MSG_QUEUE_MAX){
        t->MsgQueueTail = 0;
    }
    return 0;

fail2:
    if ((void*) t == NULL){
        return -1;
    }
    t->MsgQueueTail++;
    if (t->MsgQueueTail >= MSG_QUEUE_MAX){
        t->MsgQueueTail = 0;
    }
fail:
    return (int) -1;
}


// ------------------------------------
// post_message_to_tid:
// #bugbug
// long1 and long2 will mask to single byte.
// IN: tid, window, message code, ascii code, raw byte.
// Post message.
// Async
int
post_message_to_tid ( 
    tid_t sender_tid,
    tid_t receiver_tid,
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
// #todo:
// Nao podemos deixar que toda vez que uma thread receber uma mensagem 
// ela exija um timeout. Pois uma aplicaçao pode enviar mensagens em loop.
// Talvez isso deva ser permitido somente para mensagens de input vindas
// dos device drivers.

// Target thread.
    struct thread_d *t;
    struct msg_d *m;
    int MessageCode=0;
    // #test
    int UseTimeout=TRUE;

// TIDs
    tid_t src_tid = (tid_t) (sender_tid & 0xFFFF);
    tid_t dst_tid = (tid_t) (receiver_tid & 0xFFFF);

// Message code.
    MessageCode = (int) (msg & 0xFFFFFFFF);
    if (MessageCode <= 0){
        goto fail;
    }
// tid
    if ( dst_tid < 0 || dst_tid >= THREAD_COUNT_MAX ){
        panic("post_message_to_tid: dst_tid\n");
        //goto fail;
    }
// structure
    t = (struct thread_d *) threadList[dst_tid];
    if ((void *) t == NULL){
        panic ("post_message_to_tid: t\n");
    }
    if ( t->used != TRUE || t->magic != 1234 ){
        panic("post_message_to_tid: t validation\n");
    }
    if (t->tid != dst_tid){
        panic("post_message_to_tid: t->tid != dst_tid\n");
    }

// #test
// This thread needs a timeout.
// Let's tell to ts.c that this thread needs a timeout.
// So this way the ts can break the round and 
// give to this thread the opportunity to run immediately.
// #bugbug
// A malicious process could send a lot of messages
// causing starvation in the other threads?

    if (UseTimeout==TRUE)
    {
        //if (MessageCode == MSG_KEYDOWN)
        //{
            timeout_thread = (struct thread_d *) t;
            timeout_thread->waiting_for_timeout = TRUE;
        //}
    }

//
// The message
//

// ==========================================================
// Vamos colocar essa mensagem na outra fila de mensagens.
// Essa nova fila sera a única fila no futuro.

// Get the pointer for the next entry.
    m = (struct msg_d *) t->MsgQueue[ t->MsgQueueTail ];
    if ((void*) m == NULL){
        panic ("post_message_to_tid: m\n");
    }
    if ( m->used != TRUE || m->magic != 1234 ){
        panic ("post_message_to_tid: m validation\n");
    }

// --------------------------
// Standard header
    m->opaque_window = NULL;
    m->msg   = (int) (MessageCode & 0xFFFFFFFF);
    m->long1 = (unsigned long) long1;
    m->long2 = (unsigned long) long2;

// --------------------------
// Extra payload
    m->long3 = (unsigned long) jiffies;
    m->long4 = (unsigned long) jiffies;

// --------------------------
// Identification field
    m->sender_tid   = (tid_t) src_tid; 
    m->receiver_tid = (tid_t) dst_tid;
    //m->sender_pid = ?;
    //m->receiver_pid = ?;

// --------------------------
    m->next = NULL;

// Done
    t->MsgQueueTail++;
    if (t->MsgQueueTail >= MSG_QUEUE_MAX){
        t->MsgQueueTail = 0;
    }
    return 0;

fail2:
    if ((void*) t == NULL){
        return -1;
    }
    t->MsgQueueTail++;
    if (t->MsgQueueTail >= MSG_QUEUE_MAX){
        t->MsgQueueTail = 0;
    }
fail:
    return (int) -1;
}

// Service 112
// Post message to tid.
// Asynchronous.
unsigned long
sys_post_message_to_tid( 
    int tid, 
    unsigned long message_buffer )
{
    tid_t src_tid = (tid_t) current_thread;   // caller's tid.
    tid_t dst_tid = (tid_t) tid;              // targt tid.

// Invalid target tid.
    if ( dst_tid < 0 || dst_tid >= THREAD_COUNT_MAX ){
        return 0;
    }
// Message buffer
    if (message_buffer == 0){
        return 0;
    }
    unsigned long *buf = (unsigned long *) message_buffer;
// Message code
    int MessageCode = (int) ( buf[1] & 0xFFFFFFFF );

// Post message.
// Asynchronous.
// IN: target tid, opaque struct pointer, msg code, data1, data2.
// #todo: get the return value?

    post_message_to_tid(
        (tid_t) src_tid,    // sender tid
        (tid_t) dst_tid,    // receiver tid
        (int) MessageCode,
        (unsigned long) buf[2],
        (unsigned long) buf[3] );

    return 0;
}

// Post message to the foreground thread.
int
post_message_to_foreground_thread ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    if ( foreground_thread < 0 || foreground_thread >= THREAD_COUNT_MAX ){
        return -1;
    }
    if (msg<0){
        return -1;
    }
// #todo: Sender?
    return (int) post_message_to_tid(
                     (tid_t) 0, 
                     (tid_t) foreground_thread,
                     (int) msg, 
                     (unsigned long) long1,
                     (unsigned long) long2 );
}

int
post_message_to_ws ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
//  Post msg to the display server's tid.

// #bugbug
// We can't send messages to the display server
// when the server was closed.
// Ex: Right after we close the demo ENG.BIN
// using control + c.
// It is because the thread will have an invalid pointer.
    // #test: KERNEL_MESSAGE_TID
    tid_t src_tid = 0;   // sender tid #todo
    tid_t dst_tid = -1;  // receiver tid

    if (WindowServerInfo.initialized != TRUE){
        return -1;
    }
    dst_tid = (tid_t) WindowServerInfo.tid;
    if ( dst_tid < 0 || dst_tid >= THREAD_COUNT_MAX ){
        return -1;
    }

    //if(msg==MSG_MOUSEMOVE){
    //    printf ("x:%d y:%d\n",long1, long2);
    //    refresh_screen();
    //}

// #todo
// precisamos de uma flag que indique que isso deve ser feito.
// See: tlib.c
// IN: tid, window pointer, msgcode, data1, data2.

    post_message_to_tid(
        (tid_t) src_tid,  // sender tid
        (tid_t) dst_tid,  // receiver tid
        (int) msg,
        (unsigned long) long1,
        (unsigned long) long2 );

   return 0;
}

int
post_message_to_init ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
//  Post msg to the display server's tid.

// #bugbug
// We can't send messages to the display server
// when the server was closed.
// Ex: Right after we close the demo ENG.BIN
// using control + c.
// It is because the thread will have an invalid pointer.
    // #test: KERNEL_MESSAGE_TID
    tid_t src_tid = KERNEL_MESSAGE_TID;   // sender tid #todo
    tid_t dst_tid = INIT_TID;  // receiver tid

// Is this a valid destination?
    if ( dst_tid < 0 || dst_tid >= THREAD_COUNT_MAX ){
        return -1;
    }

    //if(msg==MSG_MOUSEMOVE){
    //    printf ("x:%d y:%d\n",long1, long2);
    //    refresh_screen();
    //}

// #todo
// precisamos de uma flag que indique que isso deve ser feito.
// See: tlib.c
// IN: tid, window pointer, msgcode, data1, data2.

    post_message_to_tid(
        (tid_t) src_tid,  // sender tid
        (tid_t) dst_tid,  // receiver tid
        (int) msg,
        (unsigned long) long1,
        (unsigned long) long2 );

   return 0;
}


int 
cali_post( 
    tid_t sender_tid,
    tid_t receiver_tid,
    struct msg_d *message )
{
// #todo: Not tested yet.
// #todo: Explain this routine.

    if (sender_tid<0){
        return -1;
    }
    if (receiver_tid<0){
        return -1;
    }
    if ((void*) message == NULL){
        return -1;
    }
    message->sender_tid   = (tid_t) sender_tid;
    message->receiver_tid = (tid_t) receiver_tid;
// Post
    return (int) post_message_to_tid( 
                     (tid_t) sender_tid,
                     (tid_t) receiver_tid,
                     (int) message->msg,
                     (unsigned long) message->long1,
                     (unsigned long) message->long2 );
}

/*
 * sys_get_message:
 *     Get a message from the current thread and 
 * put it into the given buffer.
 *     The message has 6 standard elements.
 */
// Called by sci.c
// Service 111.
// It is called by the applications.
// It is also used for ipc.

void *sys_get_message(unsigned long ubuf)
{
    unsigned long *message_address = (unsigned long *) ubuf;
    register struct thread_d *t;
    register struct msg_d *m;

// buffer
// #todo: Check some other invalid address.
    if (ubuf == 0){
        panic ("sys_get_message: ubuf\n");
        //return NULL;
    }

// Thread
// Essa é a thread que chamou esse serviço.
    if (current_thread<0 || current_thread>=THREAD_COUNT_MAX){
        return NULL;
    }
// structure
    t = (void *) threadList[current_thread];
    if ( (void *) t == NULL ){
        panic ("sys_get_message: t\n");
    }
    if (t->used != TRUE || t->magic != 1234){
        panic ("sys_get_message: t validation\n");
    }

// ===========================================================
// usando a fila de mensagens com estrutura.

// Get the next head pointer.
    m = (struct msg_d *) t->MsgQueue[ t->MsgQueueHead ];
    if ((void*) m == NULL){
        goto fail0;
    }
    if (m->used != TRUE || m->magic != 1234){
        goto fail0;
    }

// Invalid message code
    if (m->msg <= 0){
        goto fail0;
    }

// ---------------------------------
// Get standard header
    message_address[0] = (unsigned long) m->opaque_window;
    message_address[1] = (unsigned long) (m->msg & 0xFFFFFFFF);
    message_address[2] = (unsigned long) m->long1;
    message_address[3] = (unsigned long) m->long2;

// ---------------------------------
// Get the extra payload
// The data here depends on the message code,
    message_address[4] = (unsigned long) m->long3;
    message_address[5] = (unsigned long) m->long4;

// ---------------------------------
// Get the identification field
    message_address[8] = (unsigned long) m->sender_tid;
    message_address[9] = (unsigned long) m->receiver_tid;
    // We also have these elements. 
    //m->sender_pid
    //m->receiver_pid

//
// Jiffies
//

// ---------------------------------
// Jiffies when the message was posted by the kernel.
    message_address[10] = (unsigned long) m->long3; 
// ---------------------------------
// Jiffies when gotten by the app.
    message_address[11] = (unsigned long) jiffies;

// ----------------------------
// Clear the entry.
// Consumimos a mensagem. Ela não existe mais.
// Mas preservamos a estrutura.

    // Standard header
    m->opaque_window = NULL;
    m->msg = 0;
    m->long1 = 0;
    m->long2 = 0;
    // Extra payload
    m->long3 = 0;
    m->long4 = 0;
    // Identification field
    m->sender_tid = 0;
    m->receiver_tid = 0;
    m->sender_pid = 0;
    m->receiver_pid = 0;

// Done
// Yes, We have a message.
// round
    t->MsgQueueHead++;
    if (t->MsgQueueHead >= MSG_QUEUE_MAX){
        t->MsgQueueHead=0;
    }
    return (void *) 1;  //#bugbug

fail0:
// No message
// round
    if ((void*) t == NULL){
        return NULL;
    }
    t->MsgQueueHead++;
    if (t->MsgQueueHead >= MSG_QUEUE_MAX){
        t->MsgQueueHead=0;
    }
    return NULL;
}

// 120
// Get a message given the index.
// With restart support.
// IN: buffer, index, flag: TRUE=restart the queue at the end.

void *sys_get_message2(
    unsigned long ubuf, 
    int index, 
    int restart)
{
    unsigned long *message_address = (unsigned long *) ubuf;
    register struct thread_d *t;
    register struct msg_d *m;

// buffer
// #todo: Check some other invalid address.
    if ( ubuf == 0 ){ 
        panic ("sys_get_message2: ubuf\n");
        //return NULL;
    }

// Thread
// Essa é a thread que chamou esse serviço.

    if (current_thread<0 || current_thread>=THREAD_COUNT_MAX){
        return NULL;
    }

// Structure
    t = (void *) threadList[current_thread];
    if ((void *) t == NULL){
        panic ("sys_get_message2: t\n");
    }
    if ( t->used != TRUE || t->magic != 1234 ){
        panic ("sys_get_message2: t validation\n");
    }

// Get the index.
    if( index<0 || index >= MSG_QUEUE_MAX){
        goto fail0;
    }
    t->MsgQueueHead = (int) (index & 0xFFFFFFFF);

// ===========================================================
// usando a fila de mensagens com estrutura.

// Get the next head pointer.
    m = (struct msg_d *) t->MsgQueue[ t->MsgQueueHead ];
    if ((void*) m == NULL){
        goto fail0;
    }
    if (m->used != TRUE || m->magic != 1234){
        goto fail0;
    }

// Invalid message code.
    if (m->msg <= 0){
        goto fail0;
    }

// -----------------------------
// Get standard header
    message_address[0] = (unsigned long) m->opaque_window;
    message_address[1] = (unsigned long) (m->msg & 0xFFFFFFFF);
    message_address[2] = (unsigned long) m->long1;
    message_address[3] = (unsigned long) m->long2;

// -----------------------------
// Get extra payload
    message_address[4] = (unsigned long) m->long3;
    message_address[5] = (unsigned long) m->long4;

// -----------------------------
// Get identification field
    message_address[8] = (unsigned long) m->sender_tid;
    message_address[9] = (unsigned long) m->receiver_tid;
    // We also have these elements. 
    //m->sender_pid
    //m->receiver_pid

//
// Jiffies
//

// -----------------------------
// Jiffies when the message was posted by the kernel.
    message_address[10] = (unsigned long) m->long3; 

// -----------------------------
// Jiffies when gotten by the app.
    message_address[11] = (unsigned long) jiffies;

// -------------------------------------------------
// Clear the entry.
// Consumimos a mensagem. Ela não existe mais.
// Mas preservamos a estrutura.

    // Standard header
    m->opaque_window = NULL;
    m->msg = 0;
    m->long1 = 0;
    m->long2 = 0;
    // Extra payload
    m->long3 = 0;
    m->long4 = 0;
    // Identification field
    m->sender_tid = 0;
    m->receiver_tid = 0;
    m->sender_pid = 0;
    m->receiver_pid = 0;

// ==================================

// Done
// It is a valid thread pointer.
    if (restart == TRUE)
    {
        t->MsgQueueHead=0;
        t->MsgQueueTail=0;
        return (void*) 1;
    }

// Yes, We have a message.
// round
    t->MsgQueueHead++;
    if (t->MsgQueueHead >= MSG_QUEUE_MAX){
        t->MsgQueueHead = 0;
    }
    return (void *) 1;

// Is it a valid thread pointer?
fail0:
// No message.
// round
    if ((void*) t == NULL){
        return NULL;
    }
    if (restart == TRUE)
    {
        if ((void*) t != NULL){
            t->MsgQueueHead=0;
            t->MsgQueueTail=0;
        }
        return NULL;
    }
    if ((void*) t != NULL){
        t->MsgQueueHead++;
        if (t->MsgQueueHead >= MSG_QUEUE_MAX){
            t->MsgQueueHead = 0;
        }
    }
    return NULL;
}

