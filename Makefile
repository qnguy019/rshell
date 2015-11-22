CC=g++
CFLAGS=-Wall -Werror -ansi -pedantic

all: rshell

rshell: src/main.cpp src/subshell.cpp src/rshell.cpp src/shell.h src/command.h src/test.h
	$(CC) $(CFLAGS) src/main.cpp src/subshell.cpp src/rshell.cpp -o rshell &&\
	mkdir bin &&\
	mv rshell bin

test: 
	cp tests/test.sh test_command &&\
	cp tests/preced.sh precedence_test &&\
	cp tests/fulltest.sh run_fulltest

donetest:
	rm run_test &&\
	rm run_preced &&\
	rm run_fulltest

clean: 
	rm -rf bin