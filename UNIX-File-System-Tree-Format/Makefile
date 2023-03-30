CC = gcc
CFLAGS = -Wall -pedantic -std=c99
MAIN = tree
OBJS = tree.o

all: $(MAIN)

$(MAIN) : $(OBJS) tree.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -g
