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

string parse_for_comments(string command_line)
{
   string to_return = command_line;
   for (unsigned i = 0; i < command_line.size(); i++)
   {
      if (command_line.at(i) == '#')
      {
         char* store = strdup(to_return.c_str());
         char* token;
         token = strtok(store, "#");
         to_return = token;
         break;
      }
   }
   return to_return;

}
void parse_commands(queue<string>& commands, string command_line)
{
   char* store = strdup(command_line.c_str());
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

bool no_exit(queue<string> command)
{
   bool stay_while = true;
   while (!command.empty())
   {
      string command_s = command.front();
      char* token;
      char* store = strdup(command_s.c_str());
      token = strtok(store, " ");
      string check_exit = token;
      if (check_exit == "exit") 
      {
         stay_while = false;
         break;
      }
      command.pop();
    }
    return stay_while;
}
//Executes a command from the string in the command queue
//Checks if the first word of the command is exit. If so, exit the program
//Changes fail command to true if execvp returned an error (-1)
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
   else fail_command = false;
}

//returns true if exit. false if there is no exit
bool prompt(queue<string>& command_queue, queue<string>& connector_queue)
{
   string command_line;
   bool keep_loop = true;
   cout << "$: ";
   getline(cin, command_line);
   parse_commands(command_queue, command_line);
   parse_connectors(connector_queue, command_line);
   return keep_loop;

} 

void clear_queue(queue<string>& command, queue<string>& connector)
{
   while (!command.empty()) command.pop();
   while (!connector.empty()) connector.pop();

}

void print_queue(queue<string> s)
{
   while (!s.empty())
   {
      cout << s.front() << endl;
      s.pop();
   }

}

void fork_process(queue<string>& command, queue<string>& connector)
{
      while (!command.empty())
      { 
         int status;
         pid_t current_pid, w;
         current_pid = fork();
         
         if (current_pid < 0)
         {
            perror("fork()");
            exit(-1);
         }
         else if (current_pid == 0)
         {
            execute_command(command);
            exit(EXIT_FAILURE);
         }
         else 
         {
            w = waitpid(current_pid, &status, 0);
            if (w == -1) {}
            if ((WIFEXITED(status) == WEXITSTATUS(status)) != 0) fail_command = true;

            command.pop();
            if (!connector.empty())
            { bool check = true;
               while (check && !connector.empty())
               {
                  string temp_connector = connector.front();
                  connector.pop();
                  if (temp_connector == "|" && fail_command == false) command.pop();
                  if (temp_connector == "&" && fail_command == true) command.pop();
                  else break;
               }
            }
         
         } 
      }
}



//The main function that runs the shell terminal
//It has the fork process in it.
//Need to figure out how to put it in a separate function and
//still have it work
void rshell()
{
   //bool fail_command = false;
 //  queue<string> command;
 //  queue<string> connector;
   while (prompt(command, connector) && no_exit(command))
   { 
      fork_process(command, connector);
      clear_queue(command, connector);
   }
   clear_queue(command, connector);
}


#endif
