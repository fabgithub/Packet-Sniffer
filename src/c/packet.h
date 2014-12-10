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
typedef struct arphdr {
    u_int16_t htype;    /* Hardware Type           */
    u_int16_t ptype;    /* Protocol Type           */
    u_char hlen;        /* Hardware Address Length */
    u_char plen;        /* Protocol Address Length */
    u_int16_t oper;     /* Operation Code          */
    u_char sha[6];      /* Sender hardware address */
    u_char sip[4];      /* Sender IP address       */
    u_char tha[6];      /* Target hardware address */
    u_char tip[4];      /* Target IP address       */
} arphdr_t;

//Interfaces
void process_packet(unsigned char* buffer, int buffer_size);
void process_ethernet_header(unsigned char* buffer, int buffer_size);
void process_ip_header(unsigned char* buffer, int buffer_size);
void process_arp_header(unsigned char* buffer, int buffer_size);

#endif
