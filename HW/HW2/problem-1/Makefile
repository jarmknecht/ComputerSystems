CC = gcc
CFLAGS = -Wall -Iinclude
HEADER = include/struct.h

program_C_SRCS := $(wildcard *.c)

program_C_OBJS := ${program_C_SRCS:.c=.o}

default: struct

%.o:%.c
	$(CC) $(CFLAGS) -c $<

struct:$(program_C_OBJS)
	$(CC) $(CFLAGS) -o struct $(program_C_OBJS)

.phony:clean
clean:
	rm struct $(program_C_OBJS)
