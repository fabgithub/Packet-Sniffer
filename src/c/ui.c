#include "ui.h"

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

        vfprintf(file, format, file_va);

        va_end(file_va);
    }

    va_end(console_va);
}

/**
 * A simple-stupid function to print a divider.
 */
void print_divider()
{
    char buffer[41];

    memset(buffer, (int) '-', 40);
    buffer[40]='\0';

    printf("\n+%s\n", buffer);
}

/**
 * Dumps raw memory in Hex bytes and human readable text.
 *
 * Function borrowed from http://grapsus.net/blog/post/Hexadecimal-dump-in-C
 *
 * @param buffer      the buffer to print out
 * @param buffer_size length of the buffer
 */
void print_packet_data(unsigned char* buffer, int buffer_size)
{
    unsigned int i, j;

    print(0, "%s\n", "+--------< Hex Data");

    for(i = 0; i < buffer_size + ((buffer_size % HEXDUMP_COLUMNS) ? (HEXDUMP_COLUMNS - buffer_size % HEXDUMP_COLUMNS) : 0); i++)
    {
        /* print offset */
        if(i % HEXDUMP_COLUMNS == 0)
        {
            print(0, "| 0x%06x: ", i);
        }

        /* print hex data */
        if(i < buffer_size)
        {
            print(0, "%02x ", 0xFF & ((char*) buffer)[i]);
        }
        else /* end of block, just aligning for ASCII dump */
        {
            print(0, "   ");
        }

        /* print ASCII dump */
        if(i % HEXDUMP_COLUMNS == (HEXDUMP_COLUMNS - 1))
        {
            for(j = i - (HEXDUMP_COLUMNS - 1); j <= i; j++)
            {
                if(j >= buffer_size) /* end of block, not really printing */
                {
                    print(0, " ");
                }
                else if( isprint(((char*) buffer)[j]) ) /* printable char */
                {
                    print(0, "%c", 0xFF & ((char*) buffer)[j]);
                }
                else /* other char */
                {
                    print(0, ".");
                }
            }
            print(0, "\n");
        }
    }

    print(0, "%s\n", "+----------------");
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
    print(0, "| Destination Address  : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5]);
    print(0, "| Source Address       : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5]);
    print(0, "| Protocol             : %u\n", eth->h_proto);
    print(0, "|\n");
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
    print(0, "| Sender Hardware Address (MAC)   : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", arp->sha[0], arp->sha[1], arp->sha[2], arp->sha[3], arp->sha[4], arp->sha[5]);
    print(0, "| Sender IP Address               : %d.%d.%d.%d\n", arp->sip[0], arp->sip[1], arp->sip[2], arp->sip[3]);
    print(0, "| Target Hardware Address (MAC)   : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", arp->tha[0], arp->tha[1], arp->tha[2], arp->tha[3], arp->tha[4], arp->tha[5]);
    print(0, "| Target IP Address               : %d.%d.%d.%d\n", arp->tip[0], arp->tip[1], arp->tip[2], arp->tip[3]);
    print(0, "|\n");
    print(0, "| Info                            : Who has %d.%d.%d.%d? Tell %d.%d.%d.%d\n", arp->tip[0], arp->tip[1], arp->tip[2], arp->tip[3], arp->sip[0], arp->sip[1], arp->sip[2], arp->sip[3]);
    print(0, "|\n");
}

/**
 * Prints a TCP header.
 *
 * @param tcp the TCP header struct
 */
void print_tcp_header(struct tcphdr *tcp)
{
    print(0, "%s\n", "+--------< TCP Header");
    print(0, "|\n");
    print(0, "| Source Port             : %u\n", ntohs(tcp->source));
    print(0, "| Destination Port        : %u\n", ntohs(tcp->dest));
    print(0, "| Sequence Number         : %x\n", tcp->seq);
    print(0, "| Acknowledgement Number  : %x\n", tcp->ack_seq);
    print(0, "| Header Length           : %d DWORDS or %d Bytes\n", (unsigned int) tcp->doff, (unsigned int)tcp->doff * 4);
    print(0, "|\n");
    print(0, "| Urgent Flag             : %d\n", (unsigned int) tcp->urg);
    print(0, "| Acknowledgement Flag    : %d\n", (unsigned int) tcp->ack);
    print(0, "| Push Flag               : %d\n", (unsigned int) tcp->psh);
    print(0, "| Reset Flag              : %d\n", (unsigned int) tcp->rst);
    print(0, "| Synchronize Flag        : %d\n", (unsigned int) tcp->syn);
    print(0, "| Finish Flag             : %d\n", (unsigned int) tcp->fin);
    print(0, "|\n");
    print(0, "| Window                  : %d\n", ntohs(tcp->window));
    print(0, "| Checksum                : %d\n", ntohs(tcp->check));
    print(0, "| Urgent Pointer          : %d\n", ntohs(tcp->urg_ptr));
    print(0, "|\n");
}

/**
 * Prints a UDP header.
 *
 * @param udp the UDP header struct
 */
void print_udp_header(struct udphdr *udp)
{
    print(0, "%s\n", "+--------< UDP Header");
    print(0, "|\n");
    print(0, "| Source Port          : %d\n", ntohs(udp->source));
    print(0, "| Destination Port     : %d\n", ntohs(udp->dest));
    print(0, "| Length               : %d\n", ntohs(udp->len));
    print(0, "| Checksum             : %d\n", ntohs(udp->check));
    print(0, "|\n");
}
