
// tcp.c

#include <kernel.h>

static char tcp_payload[1024];

// When receiving tcp frame from NIC device.
void 
network_handle_tcp( 
    const unsigned char *buffer, 
    ssize_t size )
{
// Transport layer.
// The TCP header tracks the state of 
// communication between two TCP endpoints.

    printf("network_handle_tcp: #todo\n");

    struct tcp_d *tcp;
    tcp = (struct tcp_d *) buffer;
    register int i=0;

    if ((void*) tcp == NULL){
        printf("network_handle_tcp: tcp\n");
        return;
    }

    uint16_t sport = (uint16_t) FromNetByteOrder16(tcp->th_sport);
    uint16_t dport = (uint16_t) FromNetByteOrder16(tcp->th_dport);

    tcp_seq _seq_number = (tcp_seq) FromNetByteOrder32(tcp->th_seq);
    tcp_ack _ack_number = (tcp_ack) FromNetByteOrder32(tcp->th_ack);

// Clean the payload local buffer.
    memset(tcp_payload,0,sizeof(tcp_payload));

//
// Create a local copy of the payload.
//

    /*
    char *p2; 
    p2 = (buffer + TCP_HEADER_LENGHT);
    size_t p_size = strlen(p2);
    if (p_size <= 512)
    {
        strncpy(
            tcp_payload,
            p2,
            p_size );
        tcp_payload[p_size] = 0;
        tcp_payload[p_size +1] = 0;
    }
    tcp_payload[1021] = 0;
    */

    
    strncpy(
        tcp_payload,
        (buffer + TCP_HEADER_LENGHT),
        1020 );
    
    tcp_payload[1021] = 0;


//
// Control fields
//
    uint16_t flags = (uint16_t) FromNetByteOrder16(tcp->do_res_flags);
    //#debug
    //printf("Flags={%x}\n",flags);

// Control flags (6 bits)
    uint16_t fFIN=0;
    uint16_t fSYN=0;  // SYN :)
    uint16_t fRST=0;
    uint16_t fPUSH=0;
    uint16_t fACK=0;  // ACK :)
    uint16_t fURG=0;

    if (flags & TH_FIN){
        fFIN = 1;
    }
    if (flags & TH_SYN){
        fSYN = 1;
    }
    if (flags & TH_RST){
        fRST = 1;
    }
    if (flags & TH_PUSH){
        fPUSH = 1;
    }
    if (flags & TH_ACK){
        fACK = 1;
    }
    if (flags & TH_URG){
        fURG = 1;
    }

    // ex: 5014H
    // 0101 0000 0001 0100

//
// ports
//

    //#debug
    //printf("TCP: sport{%d}   #debug\n",sport);
    printf("TCP: dport{%d}   #debug\n",dport);

// Show
   
    if (dport == 11888)
    {
        printf ("------------------------\n");
        printf ("---- TCP -> [11888] ----\n");

        // >> Connection request: 
        // SYN=1, ACK=0
        // >> Reply: 
        // SYN=1, ACK=1

        printf("SYN={%d} ACK={%d}\n",fSYN,fACK);

        // (1) SYN
        if ( fSYN == 1 && fACK == 0 ){
            printf("\n");
            printf(">>>> [TCP] SYN     (1)\n");
            printf("SEQ={%d} | ACK={%d}\n",
                _seq_number, _ack_number);
            // #todo
            // Connect to the process that is listening at 11888.
        }
        // (2) SYN/ACK
        if ( fSYN == 1 && fACK == 1 ){
            printf("\n");
            printf(">>>> [TCP] SYN/ACK (2)\n");
            printf("SEQ={%d} | ACK={%d}\n",
                _seq_number, _ack_number);
            // #todo
            // We received a syn/ack as a response to
            // our syn sent by a process in this machine.
        }
        // (3) ACK
        if ( fSYN == 0 && fACK == 1 ){
            printf("\n");
            printf(">>>> [TCP] ACK     (3)\n");
            printf("SEQ={%d} | ACK={%d}\n",
                _seq_number, _ack_number);
            // #todo
            // We received an ack as a response to
            // our syn/ack sent by a process in this machine.
        }
    }

    //if (dport == 11888)
    //{
        //printf("TCP: MESSAGE: {%s}\n", tcp_payload );
        //memset(tcp_payload,0,sizeof(tcp_payload));
    //}
}

