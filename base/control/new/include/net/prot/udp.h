
// udp.h
// User Datagram Protocol

#ifndef __NET_UDP_H
#define __NET_UDP_H    1

#define UDP_HEADER_LENGHT  6

// UDP datagram structure
// 4*2 = 6bytes.
struct udp_d
{

// Source port number
    uint16_t uh_sport;

// Destination port number
    uint16_t uh_dport;

// Length
// This field specifies the length in bytes of the UDP header and UDP data. 
    uint16_t uh_ulen;

// Checksum
// #remember:
// When UDP runs over IPv4, 
// the checksum is computed using a "pseudo header" 
// that contains some of the same information from the real IPv4 header.
    uint16_t uh_sum;
};

void 
network_handle_udp( 
    const unsigned char *buffer, 
    ssize_t size );

void network_test_udp(void);

int
network_send_udp ( 
    uint8_t source_ip[4], 
    uint8_t target_ip[4], 
    uint8_t target_mac[6], 
    char *data_buffer,
    unsigned short port );

#endif   

