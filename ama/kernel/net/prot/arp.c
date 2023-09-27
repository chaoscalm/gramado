

// arp.c

#include <kernel.h>

unsigned char __arp_broadcast_mac[6] = { 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF 
};
unsigned char __arp_target_mac[6] = { 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF 
};
unsigned char __arp_gramado_default_ipv4[4] = { 
    0, 0, 0, 0 
};
unsigned char __arp_target_default_ipv4[4]  = { 
    192, 168, 1, 1 
};
unsigned char __arp_gateway_default_ipv4[4] = { 
    192, 168, 1, 1 
};


// When receving ARP packet from NIC device.
// handle arp package
// IN:
// buffer = The address after the ethernet header.
void 
network_handle_arp( 
    const unsigned char *buffer, 
    ssize_t size )
{
// Called by network_on_receiving() in network.c.
// 0x0806

// The buffer.
    struct ether_arp *ar;
    ar = (struct ether_arp *) buffer;

    char message[512];
    memset(message,0,sizeof(message));
    sprintf(message,"Hello from Gramado to Linux\n");

    if ((void*) ar == NULL){
        printf("network_handle_arp: ar\n");
        goto fail;
    }

// The minimum size.
// Only the udp header.
    //if (size < ARP_HEADER_LENGHT){
    //    printf("network_handle_arp: size\n");
    //    goto fail;
    //}


/*
// Show data.
// Bytes: Net-style.
// Hardware type (HTYPE)   (00 01) = Ethernet.
    printf("Hardware type: {%x}\n",ar->type);
// Protocol type (PTYPE)   (08 00) = ipv4.
// In the case of Ethernet, a 0x0806 EtherType value 
// is used to identify ARP frames.
    printf("Protocol type: {%x}\n",ar->proto);
    printf("Hardware address lenght: {%x}\n",ar->hlen);
    printf("Protocol address lenght: {%x}\n",ar->plen);
    printf("ARP operation {%x}\n",ar->op);
    // continua: macs e ips ... 
*/

// Operation
    uint16_t op = (uint16_t) FromNetByteOrder16(ar->op);


// REQUEST
// Sending a reply.
// sha is the [mac] of the machine that sent us a request.
// spa is the [ip    ] of the machine that sent us a request.
    if (op==ARP_OPC_REQUEST){
        //printf("ARP: REQUEST\n");
        network_send_arp_reply( ar->arp_sha, ar->arp_spa );
// REPLY
    } else if (op==ARP_OPC_REPLY){

        printf("ARP: REPLY from %d.%d.%d.%d\n",
            ar->arp_spa[0], 
            ar->arp_spa[1], 
            ar->arp_spa[2], 
            ar->arp_spa[3] );

        // From gateway?
        // #todo:
        // We got to use the ipv4 given by the dhcp dialog.
        if ( ar->arp_spa[0] == 192 && 
             ar->arp_spa[1] == 168  && 
             ar->arp_spa[2] == 1  &&
             ar->arp_spa[3] == 1 )
        {
            // Show MAC
            //printf("ARP:  MAC found %x.%x.%x.%x.%x.%x\n",
                //ar->arp_sha[0], 
                //ar->arp_sha[1], 
                //ar->arp_sha[2], 
                //ar->arp_sha[3],
                //ar->arp_sha[4],
                //ar->arp_sha[5] );

            // Save into the default network info.
            if ( (void*) CurrentNetwork != NULL )
            {
                if ( CurrentNetwork->initialized == TRUE )
                {
                    printf ("Saving gateway info\n");
                    network_fill_ipv4( 
                        CurrentNetwork->gateway_ipv4,
                        ar->arp_spa );
                    network_fill_mac( 
                        CurrentNetwork->gateway_mac,
                        ar->arp_sha );

                    // Show saved MAC
                    //printf("ARP:  Saved MAC %x.%x.%x.%x.%x.%x\n",
                        //CurrentNetwork->gateway_mac[0], 
                        //CurrentNetwork->gateway_mac[1], 
                        //CurrentNetwork->gateway_mac[2], 
                        //CurrentNetwork->gateway_mac[3],
                        //CurrentNetwork->gateway_mac[4],
                        //CurrentNetwork->gateway_mac[5] );
                }
            }
            //die();
        }

        // Show IP
        //printf("ARP: REPLY to %d.%d.%d.%d\n",
        //    ar->arp_tpa[0], ar->arp_tpa[1], ar->arp_tpa[2], ar->arp_tpa[3] );

        /*
        // to me
        if ( ar->arp_tpa[3] == 12 )
        {
            printf("ARP: Reply to ME!\n");
            printf("ARP:  MAC found %x.%x.%x.%x.%x.%x\n",
                ar->arp_sha[0], 
                ar->arp_sha[1], 
                ar->arp_sha[2], 
                ar->arp_sha[3],
                ar->arp_sha[4],
                ar->arp_sha[5] );
            //refresh_screen();
            //while(1){}

            // #todo
            // Save this values to use in the future.
            // see:  udp.c
            network_save_mac(ar->arp_sha);
        }
        */
    };

    return;
fail:
    printf("network_handle_arp: Fail\n");
    return;
}


// Ethernet + arp
void 
network_send_arp( 
    uint8_t target_mac[6],
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    int op )
{
// Send ARP.

    struct ether_header *eh;
    struct ether_arp *h;
    register int i=0;

    // #debug
    //printf("network_send_arp:\n");
    //refresh_screen();

// The structure for the Intel NIC device.
    if ( (void*) currentNIC == NULL ){
        printf ("network_send_arp: currentNIC fail\n");
        goto fail;
    }

// A given IP number for Gramado.
// Saving it into the NIC structure.
// 192.168.1.12
    currentNIC->ip_address[0] = source_ip[0];  //192;
    currentNIC->ip_address[1] = source_ip[1];  //168;
    currentNIC->ip_address[2] = source_ip[2];  //1;
    currentNIC->ip_address[3] = source_ip[3];  //12;

//==============================================
// # ethernet header #
    eh = (void *) kmalloc( sizeof(struct ether_header) );
    if ( (void *) eh == NULL){
        printf ("network_send_arp: eh struct fail\n");
        goto fail;
    }
// MAC
// Save the source and the destination mac into the ethernet header.
// The destination mac came via argument.
    for ( i=0; i<ETH_ALEN; i++){
        eh->mac_src[i] = (uint8_t) currentNIC->mac_address[i];
        eh->mac_dst[i] = (uint8_t) target_mac[i];
    };
// TYPE
    eh->type = (uint16_t) ToNetByteOrder16(ETH_TYPE_ARP);

//==============================================
// # arp header #
    h = (void *) kmalloc ( sizeof(struct  ether_arp) );
    if ( (void *) h == NULL ){
        printf ("network_send_arp: struct h fail");
        goto fail;
    }

//
// Header
// see: arp.h
//

// Hardware type (HTYPE)   (00 01) = Ethernet.
    h->type = (uint16_t) 0x0100;
// Protocol type (PTYPE)   (08 00) = ipv4.
// In the case of Ethernet, a 0x0806 EtherType value 
// is used to identify ARP frames.
    h->proto = (uint16_t) 0x0008;
// Hardware address length (MAC)
    h->hlen = (uint8_t) ETH_ALEN;
// Protocol address length (IP)
    h->plen = (uint8_t) 4;
// Operation (OPER)
// We only have two valid operation codes.
    if (op != ARP_OPC_REQUEST && op != ARP_OPC_REPLY){
        panic("network_send_arp: Invalid operation code\n");
    }
    h->op = (uint16_t) ToNetByteOrder16(op);

//
// Addresses
//

// MAC addresses
// Hardware address
    for ( i=0; i<ETH_ALEN; i++ ){
        h->arp_sha[i] = (uint8_t) currentNIC->mac_address[i];  //my MAC
        h->arp_tha[i] = (uint8_t) target_mac[i]; 
    };
// IP addresses
// Protocol address
    for ( i=0; i<4; i++ ){
        h->arp_spa[i] = (uint8_t) source_ip[i]; 
        h->arp_tpa[i] = (uint8_t) target_ip[i]; 
    };

//==================================
// #debug
// show arp header.

/*
    printf("\n\n");
    printf("[arp]\n\n");
    printf("type={%x} proto={%x} hlen={%d} plen={%d} op={%x} \n", 
        h->type ,h->proto ,h->hlen ,h->plen ,h->op);
    printf("\n sender: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_sha[i]); }
    printf("\n sender: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_spa[i]); }
    printf("\n target: mac ");
    for( i=0; i<6; i++){ printf("%x ",h->arp_tha[i]); }
    printf("\n target: ip ");
    for( i=0; i<4; i++){ printf("%d ",h->arp_tpa[i]); }
    refresh_screen();
    while(1){}
*/
//==================================

//
// Buffer
//

// Set up the pointers for the copy.

// Offset do endereço do buffer.
// Estamos pegando o offset que nos leva ao endereço do buffer.
// Pegamos esse offset na estrutura do controlador nic intel.
// see: nicintel.h

// pega o tail antigo.
    //unsigned long address = (currentNIC->registers_base_address + 0x3810); //head
    //unsigned long address = (currentNIC->registers_base_address + REG_TDT); // tail
    //unsigned int value32 = (uint16_t) *( (volatile unsigned int *) address );
    //currentNIC->tx_cur = (uint16_t) (value32 & 0xFFFF);
    uint16_t buffer_index = (uint16_t) currentNIC->tx_cur;

    //#debug
    //printf ("buffer_index {%d}\n",buffer_index);

//
// Buffer
//

// Let's call it 'frame'.
// Because we're sending a frame.

// Get the buffer address based on its offset.
    unsigned char *frame = 
        (unsigned char *) currentNIC->tx_buffers_virt[buffer_index];

// Get the addresses for the headers.
    unsigned char *src_ethernet = (unsigned char *) eh;
    unsigned char *src_arp      = (unsigned char *) h;


//
// Copy
//

    if ( (void*) frame == NULL )
        panic("network_send_arp: frame\n");

// Copy the ethernet header into the buffer.
// 14 bytes.
    for (i=0; i<ETHERNET_HEADER_LENGHT; i++){
        frame[i] = (unsigned char) src_ethernet[i];
    };
// Copy the arp header into the buffer.
// 28 bytes
// It starts right after the ethernet header.
    for (i=0; i<ARP_HEADER_LENGHT; i++){
        frame[ETHERNET_HEADER_LENGHT + i] = (unsigned char) src_arp[i]; 
    };

// ======================
// Sending via e1000 api.
    // 14 + 28 = 42
    size_t ARP_TOTAL_SIZE = 
        ( ETHERNET_HEADER_LENGHT + \
          ARP_HEADER_LENGHT );
// Sending a frame!
    e1000_send( currentNIC, ARP_TOTAL_SIZE, frame );
    //printf ("Done\n");
    return;
fail:
    return;
}

// Request to gateway
void network_send_arp_request(void)
{
// Send ARP request to 192.168.1.6.
    //if (networkGetStatus() != TRUE)
    //   return;
    // IN: src ipv4, dst ipv4, dst mac.
    network_arp_request_to( 
        __arp_gramado_default_ipv4,
        __arp_target_default_ipv4 );
}

// Request to gateway
void network_send_arp_request2(void)
{
// Send ARP request to 192.168.1.1.
    //if (networkGetStatus() != TRUE)
    //   return;
    // IN: src ipv4, dst ipv4, dst mac.
    network_arp_request_to( 
        __arp_gramado_default_ipv4,
        __arp_gateway_default_ipv4 );
}

// Send ARP request to a given ipv4.
void 
network_arp_request_to(
    uint8_t src_ipv4[4],
    uint8_t dst_ipv4[4] )
{
    if (networkGetStatus() != TRUE)
       return;
    network_send_arp( 
        __arp_broadcast_mac,   // target mac (broadcast)
        src_ipv4,  // src ip 
        dst_ipv4,  // dst ip 
        ARP_OPC_REQUEST );
}


void 
network_send_arp_reply(
    uint8_t target_mac[6],
    uint8_t target_ip[4] )
{
// Send ARP reply to 192.168.1.6.

// #bugbug
// Sending reply to broadcast

    network_send_arp( 
        target_mac,                // target mac
        __arp_gramado_default_ipv4,  // src ip 
        target_ip,       // dst ip (Linux)
        ARP_OPC_REPLY );
}





