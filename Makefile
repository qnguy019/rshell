CC=g++
CFLAGS=-Wall -Werror -ansi -pedantic

all: rshell

rshell: src/main.cpp src/rshell.h src/command.h
	$(CC) $(CFLAGS) src/main.cpp -o rshell &&\
	mkdir bin &&\
	mv rshell bin

test: 
	cp tests/test.sh run_test &&\
	cp tests/preced.sh run_preced &&\
	cp tests/fulltest.sh run_fulltest

donetest:
	rm run_test &&\
	rm run_preced &&\
	rm run_fulltest

clean: 
	rm -rf bin