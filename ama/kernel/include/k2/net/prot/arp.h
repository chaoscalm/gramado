
// arp.h

#ifndef __NET_ARP_H 
#define __NET_ARP_H    1

// See: 
// https://en.wikipedia.org/wiki/Address_Resolution_Protocol

// Operation codes.
#define ARP_OPC_REQUEST  0x0001
#define ARP_OPC_REPLY    0x0002

// ARP header length
#define ARP_HEADER_LENGHT  28

// arp struct
struct ether_arp 
{

//====================
//Header

    uint16_t  type;   // Hardware type (HTYPE)
    uint16_t  proto;  // Protocol type (PTYPE)
    uint8_t   hlen;   // Hardware address length 
    uint8_t   plen;   // Protocol address length 
    uint16_t  op;     // Operation (OPER)

//====================
//Addresses

// src mac
    uint8_t arp_sha[ETH_ALEN];  // Sender Hardware Address, mac 
// src ip
    uint8_t arp_spa[4];         // Sender Protocol Address, ip 

// dst mac
    uint8_t arp_tha[ETH_ALEN];  // Target Hardware Address, mac
// dst ip
    uint8_t arp_tpa[4];         // Target Protocol Address, ip

} __attribute__((packed)); 


/*
// arp cache item
struct arp_cache_item_d
{
    int used;
    int magic;
    uint8_t mac_address[6];
    uint8_t ipv4_address[4];
};
*/



// =====================================


void 
network_handle_arp( 
    const unsigned char *buffer, 
    ssize_t size );

void 
network_send_arp( 
    uint8_t target_mac[6],
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    int op );

// Send ARP request to a given ipv4.
void 
network_arp_request_to(
    uint8_t src_ipv4[4],
    uint8_t dst_ipv4[4] );
void network_send_arp_request(void);
void network_send_arp_request2(void);

void 
network_send_arp_reply(
    uint8_t target_mac[6],
    uint8_t target_ip[4] );

#endif    


