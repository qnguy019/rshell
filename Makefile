CC=g++
CFLAGS=-Wall -Werror -ansi -pedantic

all: rshell

rshell: src/main.cpp src/rshell.h 
	$(CC) $(CFLAGS) src/main.cpp -o rshell && mkdir bin && mv rshell bin

clean: 
	rm -rf bin
