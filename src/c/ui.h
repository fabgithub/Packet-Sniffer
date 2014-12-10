#ifndef UI_H
#define UI_H

#include "includes.h"

void print_welcome_message();
void print(FILE *file, const char *format, ...);
void print_ip_header(struct iphdr *iph);

#endif
