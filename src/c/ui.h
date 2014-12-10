#ifndef UI_H
#define UI_H

#define HEXDUMP_COLUMNS 8

#include "includes.h"
#include "packet.h"

void print_welcome_message();
void print(FILE *file, const char *format, ...);
void print_packet_data(unsigned char* buffer, int buffer_size);
void print_ethernet_header(struct ethhdr *eth);
void print_ip_header(struct iphdr *ip);
void print_arp_header(struct arphdr_t *arp);
void print_tcp_header(struct tcphdr *tcp);
void print_udp_header(struct udphdr *udp);

#endif
