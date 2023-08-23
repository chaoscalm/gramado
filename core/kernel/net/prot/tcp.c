
// tcp.c

#include <kernel.h>

static char tcp_payload[1024];

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

    uint16_t _fin=0;
    if (flags & TH_FIN){ _fin = 1; }
    uint16_t _syn=0;
    if (flags & TH_SYN){ _syn = 1; }
    uint16_t _rst=0;
    if (flags & TH_RST){ _rst = 1; }
    uint16_t _push=0;
    if (flags & TH_PUSH){ _push = 1; }

    uint16_t _ack=0;
    if (flags & TH_ACK){ _ack = 1; }
    uint16_t _urg=0;
    if (flags & TH_URG){ _urg = 1; }

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
        // >> Connection request: 
        // SYN=1, ACK=0
        // >> Reply: 
        // SYN=1, ACK=1

        printf("SYN={%d} ACK={%d}\n",_syn,_ack);

        if ( _syn == 1 && _ack == 0 ){
            printf(">>>> [TCP] Connection request\n");
        }
        if ( _syn == 1 && _ack == 1 )
        {
            printf(">>>> [TCP] Reply\n");
            //for (i=0; i<512; i++){ printf("%x",tcp_payload[i]); }
            //printf("\n");
        }
    }

    //if (dport == 11888)
    //{
        //printf("TCP: MESSAGE: {%s}\n", tcp_payload );
        //memset(tcp_payload,0,sizeof(tcp_payload));
    //}
}

