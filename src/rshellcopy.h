#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

bool parse_commands(queue<string>& commands, string command_line)
{
   cout << "Beginning of Parse Commands" << endl;
   bool keep_loop = true;
   vector<string> ref;
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
        ref.push_back(token);
        token = strtok(NULL, ";||&&" );
      }
   }

   cout << "Middle of Parse Commands" << endl;
   for (int q = 0; q < ref.size(); q++)
  {
     cout << ref.at(q) << endl;
   }

   //parse individual commands
   for(int i = 0; i < ref.size(); i++)
   {
      string real_command;
      string temp_command = ref.at(i);

      store = strdup(temp_command.c_str());
      token = strtok(store, " ");
      real_command = real_command + token + " ";
      token = strtok(NULL, " ");
      while (token != NULL)
      {
         real_command = real_command + token;
         token = strtok(NULL, " ");
      }
      cout << "Real Command: " << real_command << endl;
      commands.push(real_command);
    
   }
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
//returns true if exit. false if there is no exit
bool prompt(queue<string>& command_queue, queue<string>& connector_queue)
{
   string command_line;
   bool keep_loop = true;
   cout << "$: ";
   getline(cin, command_line);
   keep_loop = parse_commands(command_queue, command_line);
   parse_connectors(connector_queue, command_line);

/*
   char* store_char = strdup(command_line.c_str());
   char* token;
   token = strtok(store_char, ";||&&");
   while (token != NULL)
   {
      string temp = token;
      if (temp == "exit")
      {
         keep_loop = false;
         break;
      }
      else
      {
        ref.push_back(token);
        token = strtok(NULL, ";||&&" );
      }
   }
*/
   return keep_loop;

} 


void rshell()
{
   queue<string> command;
   queue<string> connector;

   while(prompt(command, connector))
   {


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
