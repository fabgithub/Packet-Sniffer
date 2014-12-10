#include "ui.c"

void print_welcome_message()
{

}

/**
 * Prints to both file and console.
 *
 * @param file a pointer to the file to print to
 * @param format format options
 *
 */
void print(FILE *file, const char *format, ...)
{
    va_list file_va, console_va;

    va_start(console_va, format);

    //print to console
    vprintf(format, console_va);

    //if the pointer to the file object isn't null
    if(file)
    {
        va_copy(file_va, console_va);

        vfprintf(file, file_va);

        va_end(file_va);
    }

    va_end(console_va);
}

/**
 * Print an Ethernet Header.
 *
 * @param eth the Ethernet header struct
 */
void print_ethernet_header(struct ethhdr *eth)
{
    print(0, "%s\n", "+--------< Ethernet Header");
    print(0, "|\n");
    print(0, "| Destination Address  : %u\n", eth->h_dest);
    print(0, "| Source Address       : %u\n", eth->h_source);
    print(0, "| Protocol             : %u\n", eth->h_proto);
    print(0, "|\n");
    print(0, "%s\n", "+-------------------");
}

/**
 * Print an IP Header.
 *
 * @param iph the IP header struct
 */
void print_ip_header(struct iphdr *ip)
{
    struct sockaddr_in source, destination;

    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ip->saddr;

    memset(&destination, 0, sizeof(destination));
    destination.sin_addr.s_addr = ip->daddr;

    print(0, "%s\n", "+--------< IP Header");
    print(0, "|\n");
    print(0, "| Version              : %d\n", (unsigned int) ip->version);
    print(0, "| Header Length (IHL)  : %d DWORDS or %d Bytes\n", (unsigned int) ip->ihl, ((unsigned int)(ip->ihl)) * 4);
    print(0, "| Type Of Service      : %d\n", (unsigned int) ip->tos);
    print(0, "| Total Length         : %d Bytes (Size of Packet)\n", ntohs(ip->tot_len));
    print(0, "| Identification       : %d\n", ntohs(ip->id));
    print(0, "| Fragment Offset      : %u\n", ip->frag_off);
    print(0, "| TTL                  : %d\n", (unsigned int) ip->ttl);
    print(0, "| Protocol             : %d\n", (unsigned int) ip->protocol);
    print(0, "| Header Checksum      : %d\n", ntohs(ip->check));
    print(0, "| Source Address       : %s\n", inet_ntoa(source.sin_addr));
    print(0, "| Destination Address  : %s\n", inet_ntoa(destination.sin_addr));
    print(0, "|\n");
    print(0, "%s\n", "+-------------------");

    free(source);
    free(destination);
}

/**
 * Print an ARP header.
 *
 * @param arp the custom arp header struct, defined in `packet.h`.
 */
void print_arp_header(struct arphdr_t *arp)
{
    print(0, "%s\n", "+--------< ARP Header");
    print(0, "|\n");
    print(0, "| Hardware Type                   : %d\n", ntohs(arp->htype));
    print(0, "| Protocol Type                   : %d\n", ntohs(arp->ptype));
    print(0, "| Hardware Address Length         : %u\n", arp->hlen);
    print(0, "| Protocol Address Length         : %u\n", arp->plen);
    print(0, "| Operation                       : %d - %s\n", ntohs(arp->oper), (ntohs(arp->oper) == ARP_REQUEST) ? "ARP Request" : "ARP Reply");
    print(0, "| Sender Hardware Address (MAC)   : %u\n", arp->sha);
    print(0, "| Sender IP Address               : %u\n", arp->sip);
    print(0, "| Target Hardware Address (MAC)   : %u\n", arp->tha);
    print(0, "| Target IP Address               : %u\n", arp->tip);
    print(0, "|\n");
    print(0, "| Info                            : Who has %u? Tell %u\n", arp->tip, arp->sip);
    print(0, "|\n");
    print(0, "%s\n", "+-------------------");
}
