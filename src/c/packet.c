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
}
