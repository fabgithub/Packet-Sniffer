/**
 * This file includes all packet processing related functions.
 */
#include "packet.h"

/**
 * Process a packet received.
 *
 * @param buffer      Buffer which contains packet data
 * @param buffer_size Size of the buffer
 */
void process_packet(unsigned char* buffer, int buffer_size)
{
    //process link layer and see what protocol is being used.
    struct ethhdr *eth = (struct ethhdr *) buffer;

    switch(eth->h_proto)
    {
        case ETHERTYPE_IP: //IP
            process_ip_packet(buffer, buffer_size);

            break;

        case ETHERTYPE_ARP: //ARP
            process_arp_packet(buffer, buffer_size);

            break;

        default: //Other protocols..others in `linux/if_ether.h` and `net/ethernet.h`

            break;
    }

    //print all stats here.
}
