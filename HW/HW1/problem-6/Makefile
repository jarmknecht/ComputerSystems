CC = gcc
CFLAGS = -Wall
OBJS = array.o

default: array

%.o:%.c
	$(CC) $(CFLAGS) -c $<

array:$(OBJS)
	$(CC) $(CFLAGS) -o array $(OBJS)

.phony:clean
clean:
	rm array $(OBJS)
