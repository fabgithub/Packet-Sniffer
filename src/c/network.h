#ifndef NETWORK_H
#define NETWORK_H

#include "includes.h"

void print_network_interfaces();
int create_raw_socket();
struct ifreq* get_network_interface_flags(int sock, char *interface);
void set_promiscuous_mode(int sock, char *interface);
void unset_promiscuous_mode(int sock, char *interface)

#endif
