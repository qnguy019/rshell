#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

void parse_commands(queue<string>& commands, string command_line)
{
   char* store = strdup(command_line.c_str());
   char* token;
   //just to parse all commands into vector
   token = strtok(store, ";|&");
   while (token != NULL)
   {
      commands.push(token);
      token = strtok(NULL, ";||&&" );
   }

   //parse individual commands

}   

void parse_connectors(queue<string>& connector, string command_line)
{
   for(int i = 0; i < command_line.size(); i++)
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

void check_exit(queue<string> command)
{
   while (!command.empty())
   {
      string command_s = command.front();
      char* token;
      char* store = strdup(command_s.c_str());
      token = strtok(store, " ");
      string check_exit = token;
      if (check_exit == "exit") exit(0);
      command.pop();
    }
}
//Executes a command from the string in the command queue
//Checks if the first word of the command is exit. If so, exit the program
//Returns true if executed correctly, -1 if there was an error
bool execute_command(queue<string>& command)
{
   string command_s = command.front();
   char* token;
   char* store = strdup(command_s.c_str());
   token = strtok(store, " ");
   string check_exit = token;
   if (check_exit == "exit") exit(0);
   int pos = 0;
   char* arr[15];
   
   while (token != NULL)
   {
      arr[pos] = token;
      pos++;
      token = strtok(NULL, " ");
   }
   arr[pos] = NULL;
   
   bool error = execvp(arr[0], arr);
   delete[] arr;
   return error;
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


void rshell()
{
   queue<string> command;
   queue<string> connector;
   bool run = true;
   while(prompt(command, connector))
   { 
      check_exit(command);
      while(!command.empty())
      {
         pid_t current_pid = fork();
         
         if (current_pid < 0)
         {
            cout << "fork() error" << endl;
            exit(-1);
         }
         else if (current_pid == 0)
         {
            execute_command(command);
         }
         wait(NULL);
         command.pop();
      }
   }
}


#endif
