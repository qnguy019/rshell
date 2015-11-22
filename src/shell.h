#ifndef SHELL_H
#define SHELL_H
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

//#include "command.h"
class Command;
class Shell
{
public:
	virtual bool fork_process() = 0;
	virtual bool run_shell() = 0;
	virtual bool get_fail() = 0;

};
class Rshell : public Shell
{
protected:
	queue<Command*> command_ptrs;
	queue<string> connector;
	bool run;
	bool fail;
public:
	Rshell();
	int num_occurences(char a, string c);
	bool check_paren_count(string command_line);
	bool check_paren_empty(string command_line);
	bool check_paren_in_commands(string temp);
	bool check_connector_errors(string command_line);
	void parse_comments(string& command_line);
	void insert_command(string c);
	bool empty_command(string temp);
	bool empty_stack(stack<char> l, stack<char> r);
	bool pop_stack(stack<char> &l, stack<char> &r);
	bool parse_pointers(string& c);
	void parse_connectors(string command_line);
	void clear_queue();
	void prompt();
	void ptr_pop();
	bool fork_process();
	bool run_shell();
	bool get_fail();
};

class Subshell : public Shell
{
protected:
	string command_line;
	queue<Command*> command_ptrs;
	queue<string> connector;
	bool fail;
public:
	Subshell(string command);
	bool get_fail();
	bool check_paren_empty(string command_line);
	bool check_paren_in_commands(string temp);
	void insert_command(string c);
	bool empty_command(string temp);
	bool empty_stack(stack<char> l, stack<char> r);
	bool pop_stack(stack<char> &l, stack<char> &r);
	bool parse_pointers();
	void parse_connectors();
	void clear_queue();
	void prompt();
	void ptr_pop();
	bool fork_process();
	bool run_shell();
};
#endif