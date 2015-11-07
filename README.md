#Assignment 1: Rshell
name1 = Quynh Nguyen
ucrnetid1 = qnguy019

github = qnguy019
giturl = http://www.github.com/qnguy019/rshell.git

#Introduction
Beginner C++ coders uses a shell in order to run various commands, but how is it actually done? In my CS100 (Software Construction) class, I get to understand how a shell works by programming a simple implementation of one in C++. Users can input a command and it will be executed as if it was the real thing (almost). The command line can be consisited of two things: commands (executable(argv[0], argv)) and connectors (";", "||", "&&"). The main three functions that can make this possible are waitpid(), fork(), and execvp().
#Instructions
To download this repository:

git clone http://github.com/qnguy019/rshell.git

cd rshell

git checkout hw1

"Make" will compile the source file into an executable called rshell, create a new directory called bin, and move rshell into the directory. To execute the code, either type "bin/rshell" or cd into the bin directory and run rshell. 

In order to exit the program, simply type in "exit"

#Running Tests
I made some pre-made test commands under the tests directory : "single_command.sh" "multi_command.sh" "commented_command.sh" and "exit.sh"

If you want to run these scripts, cd into the tests directory and run ./file_name (i.e. ./single_command.sh)

#Bugs
Be aware that this program is not fully complete. I tried to find all the bugs in my program and made them output errors instead of crashing my program. Besides the system call errors that should be outputted with perror, some other errors I outputted are:

Single | and & - Error: Incorrect syntax of "||" and "&&" __
| and & at the beginning or end of the input - Error: Incorrect syntax of "||" and "&&" __
Empty command in between two connects - Error: Incorrect syntax of "||" and "&&" __
Double ;; - Error: ";;" is invalid __
; in the beginning of the command line - Error: Cannot have ";" in the beginning of command line

Other bugs: __
- entering more connectors added together ("|||||" or "&&&&&&&&") __
- "ls asfe || echo hello" does not echo hello __
 ls asfe is considered a fail command, but in my code, execvp does not return a -1 for it because technically it "executed correctly". I do not how to fix this aspect of ls. I think I have to either reformat how my fork or waitpid works, or somehow catch that it did not execute correctly. __




