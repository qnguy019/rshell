#ifndef RSHELL_H
#define RSHELL_H

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

using namespace std;

static bool fail_command = false;
static queue<string> command;
static queue<string> connector;


//Gets rid of the commands/words after the #
string parse_for_comments(string command_line)
{
   char* store = strdup(command_line.c_str());
   char* token;
   token = strtok(store, "#");
   command_line = token;
   
   return command_line;

}

//Tokens everything in between ; | & into a queue.
//It still keeps the spaces however ie " ls -a"
void parse_commands(queue<string>& commands, string command_line)
{
   string to_use = parse_for_comments(command_line);
   char* store = strdup(to_use.c_str());
   char* token;
   //just to parse all commands into queue
   token = strtok(store, ";|&");
   while (token != NULL)
   {
      string temp = token;
      commands.push(token);
      token = strtok(NULL, ";||&&" );
   }
}   

//Searches from ; | and & and puts it into connector queue
void parse_connectors(queue<string>& connector, string command_line)
{
   for(unsigned i = 0; i < command_line.size(); i++)
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

//Checks if the next command is "exit"
//Returns false if the program should exit
bool no_exit(string command)
{
   bool dont_exit = true;
   char* token;
   char* store = strdup(command.c_str());
   token = strtok(store, " ");
   string check_exit = token;
   if (check_exit == "exit") dont_exit = false;
   
   return dont_exit;
}

//Executes a command from the string in the command queue
//Converts the string from the queue  into char* []
void execute_command(queue<string>& command)//, bool fail_command)
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
   
   if (execvp(arr[0], arr) == -1)
   {
      cout << command.front() << ": command not found" << endl;
   }
}

//Outputs $ and where user can input commands
//Runs the functions to parse commands and connectors
void prompt(queue<string>& command_queue, queue<string>& connector_queue)
{
   string command_line;
   cout << "$: ";
   getline(cin, command_line);
   if (command_line == "" || command_line.at(0) == '#') return;
   parse_commands(command_queue, command_line);
   parse_connectors(connector_queue, command_line);
} 

//Empties the queue just in case there are some left over
//by the time the user inputs commands again
void clear_queue(queue<string>& command, queue<string>& connector)
{
   while (!command.empty()) command.pop();
   while (!connector.empty()) connector.pop();

}

//Returns false if there was an exit command
bool fork_process(queue<string>& command, queue<string>& connector)
{
      while (!command.empty())
      { 
         //check if the command is exit
         bool dont_exit = no_exit(command.front());
         if (dont_exit == false) return false;

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
            execute_command(command);
            exit(EXIT_FAILURE); //if the execvp didn't run successfully, return EXIT_FAILURE to parent
         }
         else 
         {
            w = waitpid(current_pid, &status, 0); //parent waits for the child.
            if (w == -1) {}
            if ((WIFEXITED(status) == WEXITSTATUS(status)) != 0) fail_command = true; //parent checks if child failed

            command.pop();
            if (!connector.empty())
            {
               bool check = true;
               while (check && !connector.empty())
               {
                  if (command.empty()) break;
                  string temp_connector = connector.front();
                  connector.pop();
                  if (temp_connector == "|" && fail_command == false) command.pop();
                  if (temp_connector == "&" && fail_command == true) command.pop();
                  else break;
               }
            }

         } 
      }
      return true;
}



//The main function that runs the shell terminal
void rshell()
{
   bool stay_while = true;
   while (stay_while)
   {
      prompt(command, connector); 
      stay_while = fork_process(command, connector);
      clear_queue(command, connector);
   }
}


#endif
