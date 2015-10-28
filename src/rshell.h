#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

bool parse_commands(queue<string>& commands, string command_line)
{
   cout << "Beginning of Parse Commands" << endl;
   bool keep_loop = true;
   char* store = strdup(command_line.c_str());
   char* token;
   //just to parse all commands into vector
   token = strtok(store, ";|&");
   while (token != NULL)
   {
      string temp = token;
      if (temp == "exit")
      {
         keep_loop = false; //if this doesnt work, make it end the function 
         break;
      }
      else
      {
        commands.push(token);
        token = strtok(NULL, ";||&&" );
      }
   }

   //parse individual commands

   cout << "End of Parse Commands" << endl;
   return keep_loop;
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

//returns if it execvp correctly
bool execute(string command)
{
   char* token;
   char* store = strdup(command.c_str());
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
   keep_loop = parse_commands(command_queue, command_line);
   parse_connectors(connector_queue, command_line);
   execute(command_queue, connector_queue);

   return keep_loop;

} 


void rshell()
{
   queue<string> command;
   queue<string> connector;
   bool run = true;
   while(run)
   { 
     run = prompt(command, connector);


   }
      while (!command.empty())
      {
         cout << "Command:" << command.front() << endl;
         if(!connector.empty()) 
         {
            cout << "Connector: " << connector.front() << endl;
            connector.pop();
         }
         command.pop();
      }

}


#endif
