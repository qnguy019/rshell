#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "test.h"

using namespace std;

class Command
{
protected:
	queue<string> command;
	queue<string> connector;
	bool fail_command;
public: 
	Command(string command_line)
	{
		fail_command = false;
		fill_queue(command_line);
	}
	void parse_commands (string command_line)
	{
		char* store = strdup(command_line.c_str());
		char* token;
		//just to parse all commands into queue
		token = strtok(store, ";|&");
		while (token != NULL)
		{
			string temp = token;
			command.push(temp);
			token = strtok(NULL, ";|&" );
		}
	}   

	//Searches from ; | and & and puts it into connector queue
	void parse_connectors(string command_line)
	{
		unsigned i;
		for(i = 0; i < command_line.size(); i++)
		{
			if (command_line.at(i) == ';')
			{
				connector.push(";");
			}
			else if (command_line.at(i) == '|')
			{
				connector.push("|");
				i++;
			}
			else if (command_line.at(i) == '&')
			{
				connector.push("&");
				i++;
			}
		}
   
	}


	void fill_queue(string command)
	{
		parse_commands(command);
		parse_connectors(command);
	}
	//Checks if the next command is "exit"
	//Returns false if the program should exit
	string check_word(string c)
	{
		char* token;
		char* store = strdup(c.c_str());
		token = strtok(store, " ");
		string check = token;
		return check;
	}
	//Returns the fail_command, which is if the last command failed or not
	bool get_fail_command()
	{
		return fail_command;
	}
	
	//Executes a command from the string in the command queue
	//Converts the string from the queue  into char* []
	void execute_command()//, bool fail_command)
	{
		string command_s = command.front();
		char* token;
		char* store = strdup(command_s.c_str());
		token = strtok(store, " ");
		int pos = 0;
		char* arr[15];
   
		while (token != NULL)
		{
			arr[pos] = token;
			pos++;
			token = strtok(NULL, " ");
		}

		arr[pos] = NULL;
   
		if (execvp(arr[0], arr) < 0)
		{
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	//returns true if no exit
	bool execute()
	{
      while (!command.empty())
      { 
         //check if the command is exit
			string first_word = check_word(command.front());
         if (first_word == "exit") return false;

         fail_command = false;
         int status;
         pid_t current_pid, w;
         current_pid = fork();
         
         if (current_pid < 0) //if pid is negative, there was an error with fork()
         {
            perror("fork()");
            exit(-1);
         }
         else if (current_pid == 0) //if pid is 0, we are in the child process
         {
				if (first_word == "test" || first_word == "[" || first_word.at(0) == '[')
				{
					Test* new_test = new Test(command.front(), first_word);
					bool yes = new_test->execute();
					if (yes == false) exit(EXIT_FAILURE);
					else exit(EXIT_SUCCESS);
				}
				else
				{
					execute_command();
					exit(EXIT_FAILURE); //if the execvp didn't run successfully, return EXIT_FAILURE to parent
				}
         }
         else 
         {
            w = waitpid(current_pid, &status, 0); //parent waits for the child. child will return -1 if execvp failed
            if (((WIFEXITED(status) == WEXITSTATUS(status)) != 0) || w == -1) fail_command = true; //parent checks if child failed
            
            command.pop();
            if (!connector.empty())
            {
               bool check = true;
               while (check && !connector.empty())
               {
						string temp_connector = connector.front();
						connector.pop();
                  if (command.empty()) break;
						else if (temp_connector == "|" && fail_command == false) command.pop();
						else if (temp_connector == "&" && fail_command == true) command.pop();
                  else break;
               }

           }
         } 
      }
		return true;
	}


};

#endif