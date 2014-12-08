/**
 * This file includes all the network related functions.
 */

#include "network.h"

/**
 * Prints all available network interfaces on the device.
 */
void print_network_interfaces()
{
    struct ifaddrs *ifaddr, *ifa;
    struct sockaddr_in *sa;
    char *addr;

    //get all interfaces
    if(getifaddrs(&ifaddr) == -1)
    {
        perror("Error: Couldn't get network interfaces.\n");
        exit(1); //fatal
    }

    //iterate over the returned linked list and print each interface
    for(ifa = ifaddr; ifa; ifa = ifa->ifa_next)
    {
        if(ifa->ifa_addr->sa_family == AF_INET)
        {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            addr = inet_ntoa(sa->sin_addr);
            printf("\t%s\tAddress: %s\n", ifa->ifa_name, addr);
        }
    }

    freeifaddrs(ifaddr);
}
