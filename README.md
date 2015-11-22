#Assignment: Rshell
name1 = Quynh Nguyen
ucrnetid1 = qnguy019

github = qnguy019
giturl = http://www.github.com/qnguy019/rshell.git

##Introduction
Beginner C++ coders uses a shell in order to run various commands, but how is it actually done? In my CS100 (Software Construction) class, I get to understand how a shell works by programming a simple implementation of one in C++. Users can input a command and it will be executed as if it was the real thing (almost). The command line can be consisited of two things: commands (executable(argv[0], argv)) and connectors (";", "||", "&&"). The main three functions that can make this possible are waitpid(), fork(), and execvp().

Assignment 1: Single commands, Multi commands, Exit command, Comments

Assignment 2: Test Command, Precedence Operators

##Instructions
To download this repository:

- git clone http://github.com/qnguy019/rshell.git
- cd rshell
- git checkout hw1

"Make" will compile the source file into an executable called rshell, create a new directory called bin, and move rshell into the directory. To execute the code, either type "bin/rshell" or cd into the bin directory and run rshell. 

In order to exit the program once it is running, simply type in "exit"
##Information
#####src
Contains: main.cpp shell.h rshell.cpp subshell.cpp command.h test.h

main.cpp: runs the main rshell function

shell.h: Abstract base class

rshell.cpp: Inherits from Shell and is the main shell for the program

subshell.cpp: Inherits from Shell and is only run if there are precedence operators

command.h: Runs/Executes all the commands

test.h: Runs the Test Command

#####tests
Contains: single_command.sh, multi_command.sh, commented_command.sh, exit.sh test.sh preced.sh fulltest.sh

single_command.sh: tests single commands

multi_command.sh: tests commands with multiple connectors

commented_command.sh: tests commands with comments placed at different spots

exit.sh: tests exit command with connectors

test.sh: tests test command with connectors

preced.sh: tests precedence operators 

fulltest.sh: combination of test and preced tests

To run all these scripts except test.sh, preced.sh, fulltest.sh, cd into the tests directory and run ./file_name (i.e. ./single_command.sh)

In order to run test scripts for test, preced, and fulltest:

- cd rshell
- make test
- ./run_test or ./run_preced or ./run_fulltest
- Once you are finished, "make donetest" in order to delete these scripts

###Makefile
   Description: This is used to compile the code and putting the executable in the created bin directory.
- _make or make all:_ compile the code, create a new bin directory, and move the executable in bin
- _make test:_ create test scripts for test command, precedence operators, and full test (see above)
- _make donetest:_ remove the test scripts
- _make clean:_ remove the bin directory and all the files it contained

##Bugs
Be aware that this program is not fully complete. I tried to find all the bugs in my program and made them output errors instead of crashing my program. Besides the system call errors that should be outputted with perror, some other errors I outputted are:

- Single | and & - _Error: Incorrect syntax of "||" and "&&"_
- | and & at the beginning or end of the input - _Error: Incorrect syntax of "||" and "&&"_ 
- Empty command in between two connects - _Error: Incorrect syntax of "||" and "&&"_ 
- Double ;; - _Error: ";;" is invalid_ 
- ; in the beginning of the command line - _Error: Cannot have ";" in the beginning of command line_
- ((echo A)) - _Error: Invalid '((' and '))'_
- Uneven amount of precedence operators - _Error: Unexpected '(' or ')'_
- Empty ( ) - _Error: Unexpected '(' or ')'_
- Too many arguments for test or [ ] - _Error: Too many arguments_
- Uneven amount of [ ] - _Error: No matching ']' for '['_
- Double [[ or ]] - _Error: Unexpected '[' or  ']'_

Note: When the actual test command only has one parameter, it defaults to -n and always returns true. Also, the test command will always return true if it has any invalid flag. The assignment only asks us to implement -e, -f, and -d, so anything else will be consider an error.

- Not enough arguments for test or [ ] - _Error: Not enough arguments_
- Any other flag besides -e, -f, -d - _Invalid Flag: For the sake of this assignment, please use -e, -f, or -d_
- Empty [ ] - _Error: Empty []_

_Other bugs:_
- entering more connectors added together ("|||||" or "&&&&&&&&")
- didn't output error if there were no spaces before and after '[' or '] (i.e [ -e LISCENSE])
- entering more brackets ("[[[[[ ]]]]]")

If I missed any errors that I put in the program and forgot to put here, you can email me at qnguy019@ucr.edu.



