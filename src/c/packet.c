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

    //check the embedded protocol in the ethernet header and process accordingly
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

/**
 * Process an IP packet.
 *
 * @param buffer      Buffer which contains packet data
 * @param buffer_size Size of the buffer
 */
void process_ip_packet(unsigned char* buffer, int buffer_size)
{
    //Get the IP header part of the packet, leaving out the ethernet header
    struct iphdr *iph = (struct iphdr *) (buffer + sizeof(struct ethhdr));



}
