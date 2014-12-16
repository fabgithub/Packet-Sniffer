# Packet Sniffer - C Implementation

Packet Sniffer, implemented in C, using raw sockets. Can capture both in promiscuous mode (for the entire network) and normal mode (just for your machine).

For now, dumps everything to console but support for dumping to files will be added soon!

## Architecture

Stars processing a packet from the bottom-up i.e., `Link Layer (Ethernet)` --> `Network Layer` --> `Transport Layer`.

Later on, support will be added for processing HTTP, FTP and other common application layer protocols.

## Files

1. `includes.h` - One place for all includes.
2. `packet.c` - Includes all the logic to process a captured packet.
3. `ui.c` - Includes all the view related stuff. Printing a packet and different parts of it (Link Layer, Network layer, Transport Layer etc.).
4. `sniffer.c` - Main entry point for the application.

## Future

- This was done just for learning purposes but to finish this up, support for processing HTTP, FTP and other common application layer protocols will be added.

- Another version of this same program will use `libpcap` instead of directly tapping into the raw socket stream. 
