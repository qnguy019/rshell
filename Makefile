CC=g++
CFLAGS=-Wall -Werror -ansi -pedantic

all: rshell

rshell: src/main.cpp src/rshell.h src/command.h
	$(CC) $(CFLAGS) src/main.cpp -o rshell &&\
	mkdir bin &&\
	mv rshell bin

test: 
	cp tests/test.sh run_test

donetest:
	rm run_test

clean: 
	rm -rf bin