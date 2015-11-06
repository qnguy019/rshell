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


//returns false if | or & was found. 
bool check_single_connectors (string command_line)
{
   char* store = strdup(command_line.c_str());
   char* token;
   token = strtok(store, " ");
   string temp = token;
   if (temp.at(0) == ';') 
   {
      cout << "Error: Cannot have \";\" in beginning of command line" << endl;
      return false;
   }
   else if (command_line.at(0) == '|' || command_line.at(0) == '&')
   {
      cout << "Error: Use \"||\" and \"&&\"" << endl;
      return false;
   }
   for(unsigned i = 0; i < command_line.size() - 1; i++)
   {
      if (command_line.at(i) == '|')
      {
         if (command_line.at(i + 1) != '|')
         {
            cout << "Error: Use \"||\" and \"&&\"" << endl;       
            return false;
         }
         else i++;
         
      }
      else if (command_line.at(i) == '&')
      {
         if (command_line.at(i + 1) != '&')
         {
            cout << "Error: Use \"||\" and \"&&\"" << endl;       
            return false;
         }
         else i++;
      }
   }
   unsigned end = command_line.size() - 1;
   if (command_line.at(end) == '|' || command_line.at(end) ==  '&')
   {
      cout << "Error: Use \"||\" and \"&&\"" << endl;
      return false;
   }
   return true;
}
  

void parse_comments(string& command_line)
{
   
   char* store = strdup(command_line.c_str());
   char* token;
   string temp, store_comm;
   token = strtok(store, " ");
   temp = token;
   while (token != NULL)
   {
      temp = token;
      if (temp.at(0) == '#')
      {
         command_line = store_comm;
         return;
      }
      store_comm = store_comm + " " + temp;
      token = strtok(NULL, " ");
   }
   command_line = store_comm;
}
   
//Tokens everything in between ; | & into a queue.
//It still keeps the spaces however ie " ls -a"
void parse_commands(queue<string>& commands, string command_line)
{
   parse_comments(command_line);
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

//Searches from ; | and & and puts it into connector queue
void parse_connectors(queue<string>& connector, string command_line)
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
   
   if (execvp(arr[0], arr) < 0)
   {
      perror(NULL);
      exit(EXIT_FAILURE);
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
   bool single_error = check_single_connectors(command_line);
   if (single_error == false) return;
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
            w = waitpid(current_pid, &status, 0); //parent waits for the child. child will return -1 if execvp failed
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
