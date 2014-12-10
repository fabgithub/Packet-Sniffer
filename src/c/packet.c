/**
 * This file includes all packet processing related functions.
 */
#include "packet.h"
#include "ui.h"

/**
 * Process a packet received.
 *
 * @param buffer      Buffer which contains packet data
 * @param buffer_size Size of the buffer
 */
void process_packet(unsigned char* buffer, int buffer_size)
{
    //process link layer and see what protocol is being used.
    process_ethernet_header(buffer, buffer_size);

    //print all stats here.
}

/**
 * Process an Ethernet header.
 *
 * @param buffer      Buffer which contains packet data
 * @param buffer_size Size of the buffer
 */
void process_ethernet_header(unsigned char* buffer, int buffer_size)
{
    struct ethhdr *eth = (struct ethhdr *) buffer;

    //print ip header
    print_ethernet_header(eth);

    //check the embedded protocol in the ethernet header and process accordingly
    switch(ntohs(eth->h_proto))
    {
        case ETHERTYPE_IP: //IP
            process_ip_header(buffer, buffer_size);

            break;

        case ETHERTYPE_ARP: //ARP
            process_arp_header(buffer, buffer_size);

            break;

        default: //Other protocols..others in `linux/if_ether.h` and `net/ethernet.h`

            break;
    }
}

/**
 * Process an IP header.
 *
 * @param buffer      Buffer which contains packet data
 * @param buffer_size Size of the buffer
 */
void process_ip_header(unsigned char* buffer, int buffer_size)
{
    //length of the ip header
    unsigned short iphdrlen;

    //Get the IP header part of the packet, leaving out the ethernet header
    struct iphdr *iph = (struct iphdr *) (buffer + sizeof(struct ethhdr));

    //set the IP header length
    iphdrlen = iph->ihl * 4;

    //print ip header
    print_ip_header(iph);

    //check the protocol embedded in the packet and process accordingly.
    switch(iph->protocol)
    {
        case 1: //ICMP
            break;

        case 6: //TCP
            process_tcp_header(buffer, buffer_size, iphdrlen);

            break;

        case 17: //UDP
            break;

        default: //other protocols
            break;
    }

}

/**
 * Process an ARP header.
 *
 * @param buffer      Buffer which contains the packet data
 * @param buffer_size Size of the buffer
 */
void process_arp_header(unsigned char* buffer, int buffer_size)
{
    //Get ARP header..leaving out the Ethernet header
    struct arphdr_t *arp = (struct arphdr_t *) (buffer + sizeof(struct ethhdr));

    //print the arp header
    print_arp_header(arp);
}

/**
 * Process a TCP header.
 *
 * @param buffer      Buffer which contains the packet data
 * @param buffer_size Size of the buffer
 * @param iphdrlen    Length of the IP Header.
 */
void process_tcp_header(unsigned char* buffer, int buffer_size, unsigned short iphdrlen)
{
    //Get the TCP header..leaving out Ethernet, IP header.
    struct tcphdr *tcp = (struct tcphdr *) (buffer + iphdrlen + sizeof(struct ethhdr));

    //print the TCP header
    print_tcp_header(tcp);
}
