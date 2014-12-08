#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <ifaddrs.h>

void print_network_interfaces();
int create_raw_socket();

#endif
