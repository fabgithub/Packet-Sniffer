#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h> //for socket()
#include <netinet/if_ether.h> //for ETH_P_ALL
#include <sys/ioctl.h> //for ioctl()
#include <net/if.h> //for interface flags, look at `man netdevice(7)` for more.
#include <ifaddrs.h> //getting network interfaces

void print_network_interfaces();
int create_raw_socket();
ifreq* get_network_interface_flags(char *interface);

#endif
