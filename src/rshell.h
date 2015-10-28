#ifndef RSHELL_H
#define RSHELL_H

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

//returns true if exit. false if there is no exit
bool prompt(vector<string>& ref)
{
   string command_line;
   bool keep_loop = true;;
   cout << "$: ";
   getline(cin, command_line);
   char* store_char = strdup(command_line.c_str());
   char* token;
   token = strtok(store_char, " ");
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
        token = strtok(NULL, " " );
      }
   }

   return keep_loop;

} 


void parse(queue<string> commands, queue<string> connectors,
vector<string> tok)
{


}
void rshell()
{
   vector<string> tokens;
   queue<string> commands;
   queue<string> connectors;

   while(prompt(tokens))
   {
     cout << "Ending" << endl;

   }
   for (int i = 0; i < tokens.size(); i++)
   {
      cout << tokens.at(i) << endl;
   }
}


#endif
