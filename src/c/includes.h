#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h> //for printf(), perror()
#include <stdarg.h> //for va_list and va_start
#include <signal.h> //for signal()
#include <stdlib.h> //malloc
#include <string.h> //memset
#include <netinet/ip.h> //IP header
#include <netinet/tcp.h> //TCP header
#include <netinet/udp.h> //UDP header
#include <netinet/ip_icmp.h> //ICMP header
#include <arpa/inet.h> //convertors
#include <net/ethernet.h> //Ethernet header
#include <sys/socket.h> //for socket()
#include <netinet/if_ether.h> //for ETH_P_ALL
#include <sys/ioctl.h> //for ioctl()
#include <net/if.h> //for interface flags, look at `man netdevice(7)` for more.
#include <ifaddrs.h> //getting network interfaces

#endif
