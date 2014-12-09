#include "includes.h"

/* Interfaces */
void signal_int();

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
    struct sockaddr saddr;
    int saddr_size, data_size;

    //register signal handler for CTRL+C
    signal(SIGINT, signal_int);
}

/**
 * Does some clean up (example: turn off the interface's promiscuous mode).
 *
 * Invoked when CTRL+C is pressed.
 */
void signal_int()
{

}
