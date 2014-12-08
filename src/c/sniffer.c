#include "includes.h"

/* Interfaces */
void signal_int();

/**
 * The main entry point of the packet sniffer.
 *
 * @param  argc Argument Count
 * @param  argv Arguments
 * @return
 */
int main(int argc, char **argv)
{

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
