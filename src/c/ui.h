#ifndef UI_H
#define UI_H

#include "includes.h"
#include "packet.h"

void print_welcome_message();
void print(FILE *file, const char *format, ...);
void print_ip_header(struct iphdr *ip);
void print_ethernet_header(struct ethhdr *eth);

#endif
