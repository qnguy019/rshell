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
make
bin/rshell

"Make" will compile the source file into an executable called rshell, create a new directory called bin, and move rshell into the directory.

In order to exit the program, simply type in "exit"

#Running Tests
I made some pre-made test commands under the tests directory : "single_command.sh" "multi_command.sh" "commented_command.sh" and "exit.sh"


