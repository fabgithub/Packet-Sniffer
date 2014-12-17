# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -W -pedantic

# the build target executable:
TARGET = psniffer

psniffer: sniffer.c ui.c network.c packet.c
	$(CC) $(CFLAGS) -o $(TARGET) *.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean:
	$(RM) psniffer *.o *~
