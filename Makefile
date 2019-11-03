CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g -pedantic
PROJ=hello

all: $(PROJ).c
	$(CC) $(CFLAGS) $(PROJ).c -o $(PROJ)
