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

static bool fail_command = false;


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

bool check_exit(queue<string> command)
{
   bool exit_program = false;
   while (!command.empty())
   {
      string command_s = command.front();
      char* token;
      char* store = strdup(command_s.c_str());
      token = strtok(store, " ");
      string check_exit = token;
      if (check_exit == "exit")
      {
         exit_program = true;
         break;
      }
      command.pop();
    }
    return exit_program;
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

   //fail_command = false;
   if (execvp(arr[0], arr) == -1)
   {
      cout << command.front() << ": command not found" << endl;
      fail_command = true;
    }
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
/*
void fork_process(queue<string> command, bool fail_command)
{


}
*/


//The main function that runs the shell terminal
//It has the fork process in it.
//Need to figure out how to put it in a separate function and
//still have it work
void rshell()
{
   //bool fail_command = false;
   queue<string> command;
   queue<string> connector;
   bool run = true;
   while (prompt(command, connector))
   { 
      if (check_exit(command)) break;
      while (!command.empty())
      {
         fail_command = false;
         pid_t current_pid = fork();
         
         if (current_pid < 0)
         {
            cout << "fork() error" << endl;
            exit(-1);
         }
         else if (current_pid == 0)
         {
            execute_command(command);//, fail_command);
         }
         wait(NULL);
         command.pop();
         if (!connector.empty())
         {
            string temp_connector = connector.front();
            connector.pop();
            if (temp_connector == "|")
            {
               if (fail_command == false) command.pop();
            }

            if (temp_connector == "&")
            {
               if (fail_command == true) command.pop();
            }
         }

      }
      clear_queue(command, connector);
   }
}


#endif
