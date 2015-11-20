#ifndef RSHELL_H
#define RSHELL

#include "command.h"
class Rshell
{
protected:
	queue<Command*> command_ptrs;
	queue<string> connector;
	bool run;
	bool fail;
public:
	Rshell()
	{
		run = true;
	}
	int num_occurences(char a, string c)
	{
		int count = 0;
		for (unsigned i = 0; i < c.size(); i++)
		{
			if (c.at(i) == a) count++;
		}
		return count;
	}
	bool check_paren_count(string command_line)
	{
		int left = num_occurences('(', command_line);
		int right = num_occurences(')', command_line);
		if (left != right)
		{
			cout << "Error: Unexpected '(' or ')'" << endl;
			return false;
		}
		return true;
	}

	//returns false if there is no command in between the ()
	bool check_paren_empty(string command_line)
	{
		return true;
	}

	//return false if there is a ( or ) in a command
	bool check_paren_in_commands(string temp)
	{
		for (unsigned j = 0; j < temp.size(); j++)
		{
			if (temp.at(j) == ')' || temp.at(j) == '(')
			{
				cout << "Error: Unexpected '(' or ')' ";
				return false;
			}
		}
		return true;
	}


	//returns false if | or & was found. 
	bool check_connector_errors(string command_line)
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
		if (command_line.find(";;") != string::npos)
		{
			cout << "Error: \";;\" is invalid" << endl;
			return false;
		}
		unsigned end = command_line.size() - 1;
		if (command_line.at(end) == '|' || command_line.at(end) ==  '&')
		{
			cout << "Error: Incorrect syntax of \"||\" and \"&&\"" << endl;
			return false;
		}
		if (command_line.at(0) == '|' || command_line.at(0) == '&')
		{
			cout << "Error: Incorrect syntax of \"||\" and \"&&\"" << endl;
			return false;
		}
		for(unsigned i = 0; i < command_line.size() - 1; i++)
		{
			if (command_line.at(i) == '|')
			{
				if (command_line.at(i + 1) != '|')
				{
					cout << "Error: Incorrect syntax of \"||\" and \"&&\"" << endl;       
					return false;
				}
				else if (command_line.at(i + 1) == ')' || command_line.at(i + 2) == ')')
				{
					cout << "Error: Unexpected '(' or ')'" << endl;
					return false;
				}
				else if (command_line.at(i - 1) == '(')
				{
					cout << "Error: Incorrect syntax of \"||\" and \"&&\"" << endl;
					return false;
				}
				else i++;
			}
			else if (command_line.at(i) == '&')
			{
				if (command_line.at(i + 1) != '&')
				{
					cout << "Error: Incorrect syntax \"||\" and \"&&\"" << endl;       
					return false;
				}
				else if (command_line.at(i + 1) == ')' || command_line.at(i + 2) == ')')
				{
					cout << "Error: Unexpected '(' or ')'" << endl;
					return false;
				}
				else if (command_line.at(i - 1) == '(')
				{
					cout << "Error: Incorrect syntax of \"||\" and \"&&\"" << endl;
					return false;
				}
				else i++;
			}
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
		//checks if theres a # before a command/connector
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
		//checks if theres a # after a connector
		for (unsigned i = 0; i < store_comm.size() - 1; i++)
		{
			if ((store_comm.at(i) == '|' || store_comm.at(i) == ';'
			|| store_comm.at(i) == '&') && store_comm.at(i + 1) == '#') 
			{
				store_comm.erase(store_comm.begin() + i, store_comm.end());
				command_line = store_comm;
				return;
			}
		}
		command_line = store_comm;
	}
	void insert_command(string c)
	{
		Command* new_comm = new Command(c);
		command_ptrs.push(new_comm);
	}
	bool empty_command(string temp)
	{
		char* store = strdup(temp.c_str());
		char* token = strtok(store, " ");
		if (token == NULL) return true;
		return false;
}
	//return false if there was a ( or ) in the command
	bool parse_pointers(string& c)
	{
		string temp;
		string for_connectors = c;
		for (unsigned i = 0; i < c.size(); i++)
		{
			if (c.at(i) == '(')
			{
				temp = "";
				i++;
				while (c.at(i)!= ')')
				{
					temp = temp + c.at(i);
					i++;
				}
				if (empty_command(temp))
				{
					cout << "Error: Unexpected '(' or ')'" << endl;
					return false;
				}
				insert_command(temp);
				int start = for_connectors.find(temp);
				--start;
				int end = temp.size() + 2;
				for_connectors.replace(start, end, "C");
				temp = "";
			}
			else if (c.at(i) == ';')
			{
				if (empty_command(temp))
				{
					temp = "";
				}
				else
				{
					insert_command(temp);
					if (check_paren_in_commands(temp) == false) return false;
					temp = "";
				}
			}
			else if (c.at(i) == '|')
			{
				if (empty_command(temp))
				{
					temp = "";
				}
				else
				{
					insert_command(temp);
					if (check_paren_in_commands(temp) == false) return false;
					temp = "";
				}
				i++;
			}
			else if (c.at(i) == '&')
			{
				if (empty_command(temp))
				{
					temp = "";
				}
				else
				{
					insert_command(temp);
					if (check_paren_in_commands(temp) == false) return false;
					temp = "";
				}
				i++;
			}
			else temp = temp + c.at(i);
		}
		if (!empty_command(temp))
		{
			insert_command(temp);
			if (check_paren_in_commands(temp) == false) return false;
		}
		c = for_connectors;
		return true;

	}
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

	void clear_queue()
	{
		while (!command_ptrs.empty())
		{
			delete command_ptrs.front();
			command_ptrs.front() = 0;
			command_ptrs.pop();
		}
		while (!connector.empty())
		{
			connector.pop();
		}
	}

	void prompt()
	{
		cout << "$: ";
		string command_line;
		getline(cin, command_line);
		if (command_line == "" || command_line.at(0) == '#') return;
		parse_comments(command_line);
		bool single_error = check_connector_errors(command_line);
		if (single_error == false) return;
		if (check_paren_count(command_line) == false) return;
		if (parse_pointers(command_line) == false) return;
		parse_connectors(command_line);
	}
	void ptr_pop()
	{
		delete command_ptrs.front();
		command_ptrs.front() = 0;
		command_ptrs.pop();
	}
	bool fork_process()
	{
		while (!command_ptrs.empty())
		{
			if (command_ptrs.front()->execute() == false) return false;
			bool fail = command_ptrs.front()->get_fail_command();
			ptr_pop();
			if (!connector.empty())
			{
				bool check = true;
            while (check && !connector.empty())
            {
					string temp_connector = connector.front();
					connector.pop();
               if (command_ptrs.empty()) break;
					else if (temp_connector == "|" && fail == false) ptr_pop();
					else if (temp_connector == "&" && fail == true) ptr_pop();
               else break;
            }
			}
		}
		return true;
	}
	void run_rshell()
	{
		while (run)
		{
			prompt();
			run = fork_process();
			clear_queue();
		}
	}

};
#endif