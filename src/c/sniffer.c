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
void process_signal();

int loop; //switch for the main loop
int raw_socket; //the descriptor of the raw socket in use
char interface[16]; //name of the interface in use
char promiscuous; //if the socket is running in promiscuous mode or not

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

    //we want to loop
    loop = 1;

    //print all available network interfaces
    printf("%s\n\n", "The available network interfaces on your machine are: ");
    print_network_interfaces();
    printf("\n%s\t", "Enter the interface that you want to sniff:");
    scanf("%s", interface); //assign the global interface

    printf("\n\n%s:\t", "Do you want to scan in promiscuous mode? (Y or N)");
    promiscuous = getchar();

    if(toupper(promiscuous) == 'Y')
    {
        //get a raw socket in a promiscuous mode
        raw_socket = create_raw_promiscuous_socket(interface);
    }
    else
    {
        //just create a raw socket
        raw_socket = create_raw_socket();
    }

    //make sure 'promiscuous mode' will get disabled upon program termination
    signal(SIGINT, process_signal); //register signal handler for CTRL+C
    atexit(process_signal);

    printf("%s: %s ..\n", "Now monitoring all packets on the interface", interface);

    //infinite loop to read - exits and does cleanup upon CTRL+C
    while(loop)
    {
        data_size = recvfrom(raw_socket, buffer, 65536, 0, NULL, NULL);

        if(data_size < 0)
        {
            printf("%s\n", "Error: Recvfrom failed to get packets!");
            exit(1);
        }

        //process the packet in the received data
        process_packet(buffer, data_size);
    }

    //we've exited the loop, do all cleanup and exit
    on_exit_cleanup();

    return 0;
}

/**
 * Does some clean up.
 *
 * (example: turn off the interface's promiscuous mode).
 */
void on_exit_cleanup()
{
    if(toupper(promiscuous) == 'Y')
    {
        //turn off the interface's promiscuous mode
        unset_promiscuous_mode(raw_socket, interface);
    }

    //close the raw socket
    close(raw_socket);
}

/**
 * Process signals that are registered with `signal()`.
 */
void process_signal()
{
    //only have SIGINT for now.
    loop = 0;
}
