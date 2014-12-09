//--------------------------------------------------------------
//
//      This program lets a user sniff network packets using the
//      Linux PF_PACKET protocol family.
//
//      Since we're using raw sockets here, the program needs
//      to be invoked as root.
//
//          $ gcc *.c -o psniff
//          $ chmod a+s psniff
//          $ sudo ./psniff
//
//      To terminate the program's execution, hit the <CONTROL-C>
//      key-combo.
//
//--------------------------------------------------------------

#include "includes.h"
#include "network.h"
#include "packet.h"

/* Interfaces */
void on_exit_cleanup();

int socket; //the descriptor of the raw socket in use
char interface[16]; //name of the interface in use

/**
 * The main entry point of the packet sniffer.
 *
 * @param  argc Argument Count
 * @param  argv Arguments
 * @return
 */
int main(int argc, char **argv)
{
    //size of the data read from the raw socket
    int data_size;

    //buffer to scan into
    unsigned char *buffer = (unsigned char *) malloc(65536);

    //print all available network interfaces
    printf("%s\n\n", "The available network interfaces on your machine are: ");
    print_network_interfaces();
    printf("\n%s\t", "Enter the interface that you want to sniff:");
    scanf("%s", interface); //assign the global interface

    //get a raw socket in a promiscuous mode
    socket = create_raw_promiscuous_socket(interface);

    //make sure 'promiscuous mode' will get disabled upon program termination
    signal(SIGINT, on_exit_cleanup); //register signal handler for CTRL+C
    atexit(on_exit_cleanup);

    printf("%s: %s ..\n", "Now monitoring all packets on the interface", interface);

    //infinite loop to read
    while(1)
    {
        data_size = recvfrom(socket, buffer, 65536, 0, NULL, NULL);

        if(data_size < 0)
        {
            printf("%s\n", "Error: Recvfrom failed to get packets!");
            exit(1);
        }

        //process the packet in the received data
        process_packet(buffer, data_size);
    }
}

/**
 * Does some clean up.
 *
 * (example: turn off the interface's promiscuous mode).
 */
void on_exit_cleanup()
{
    //turn off the interface's promiscuous mode
    unset_promiscuous_mode(socket, interface);

    //close the raw socket
    close(socket);
}
