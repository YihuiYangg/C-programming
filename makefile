# This makefile should work without needing any changes
# to compile your code, type 'make'
# to remove all .o and executable files 'make clean'

CC = gcc
CFLAGS = -Wall -Wextra -std=c99


SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

island: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f island $(OBJS)