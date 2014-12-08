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

/**
 * Creates a raw socket and returns a descriptor to it.
 *
 * @return raw socket descripter
 */
int create_raw_socket()
{
    int raw_socket;

    //create a raw socket
    if((raw_socket = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 1)
    {
        perror("Error: Couldn't open socket.\n");
        exit(0);
    }

    return raw_socket;
}

ifreq* get_network_interface_flags(char *interface)
{
    struct ifreq ifr;

    //initialize the ifreq structure
    memset(&ifr, 0, sizeof(struct ifreq));

    //set the interface to use
    strcpy(ifr.ifr_name, interface);

    //get the interface's current flags
    if(ioctl(raw_socket, SIOCGIFFLAGS, &ifr) == -1)
    {
        perror("Error: Couldn't retrieve flags from the device.\n");
        exit(0);
    }

    return *ifr;
}
