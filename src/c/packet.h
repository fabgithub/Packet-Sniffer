#ifndef PACKET_H
#define PACKET_H

#include "includes.h"

void process_packet(unsigned char* buffer, int buffer_size);
void process_ip_packet(unsigned char* buffer, int buffer_size);

#endif
