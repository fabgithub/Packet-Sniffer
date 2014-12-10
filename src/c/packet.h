#ifndef PACKET_H
#define PACKET_H

#include "includes.h"
#include "ui.h"

/**
 * ARP Header.
 *
 * Not using the one in `net/if_arp.h` because
 * it doesn't have addresses.
 */
struct arphdr_t {
    unsigned short int   htype;          /* Hardware Type           */
    unsigned short int   ptype;          /* Protocol Type           */
    unsigned char        hlen;           /* Hardware Address Length */
    unsigned char        plen;           /* Protocol Address Length */
    unsigned short int   oper;           /* Operation Code          */
    unsigned char        sha[ETH_ALEN];  /* Sender hardware address */
    unsigned char        sip[4];         /* Sender IP address       */
    unsigned char        tha[ETH_ALEN];  /* Target hardware address */
    unsigned char        tip[4];         /* Target IP address       */
    char                 padding[18];    /* Padding                 */
};

//Interfaces
void process_packet(unsigned char* buffer, int buffer_size);
void process_ethernet_header(unsigned char* buffer, int buffer_size);
void process_ip_header(unsigned char* buffer, int buffer_size);
void process_arp_header(unsigned char* buffer, int buffer_size);

#endif
