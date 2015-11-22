//#include "shell.h"
#include "command.h"

//constructor
Rshell::Rshell()
{
	run = true;
}

//returns the number of occurences of a char
int Rshell::num_occurences(char a, string c)
{
	int count = 0;
	for (unsigned i = 0; i < c.size(); i++)
	{
		if (c.at(i) == a) count++;
	}
	return count;
}

//returns false if there is an uneven amount of '(' and ')'
bool Rshell::check_paren_count(string command_line)
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
bool Rshell::check_paren_empty(string command_line)
{
	return true;
}

//return false if there is a ( or ) in a command
bool Rshell::check_paren_in_commands(string temp)
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
bool Rshell::check_connector_errors(string command_line)
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
		else if (command_line.at(i) == '(' && command_line.at(i + 1) == ';')
		{
			cout << "Error: Unexpected ';'" << endl;
			return false;
		}
	}
	return true;
}

//Removes everything after the #
void Rshell::parse_comments(string& command_line)
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

//Inserts the Command* into the queue
void Rshell::insert_command(string c)
{
	Command* new_comm = new Command(c);
	command_ptrs.push(new_comm);
}

//returns true if it was an empty command
bool Rshell::empty_command(string temp)
{
	char* store = strdup(temp.c_str());
	char* token = strtok(store, " ");
	if (token == NULL) return true;
	return false;
}

//return true if we found matching parenthesis
bool Rshell::empty_stack(stack<char> l, stack<char> r)
{
	if (l.size() == r.size()) return true;
	return false;
}

//pops the ( and ) off their respective stack. Returns true if the stack is empty
bool Rshell::pop_stack(stack<char> &l, stack<char> &r)
{
	l.pop();
	r.pop();
	return (empty_stack(l, r));
}

//returns true if there was only one command in (( ))
bool Rshell::arg_error(string c)
{
	int count = 1;
	char* store = strdup(c.c_str());
	char* token = strtok(store, "()");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, "()");
	}
	if (count > 1) return true;
	return false;
}

//return false if there was a ( or ) in the command
bool Rshell::parse_pointers(string& c)
{
	string temp;
	string for_connectors = c;
	for (unsigned i = 0; i < c.size(); i++)
	{
		if (c.at(i) == '(')
		{
			bool check_arg = false; //checking for cases like ((echo A))
			stack<char> left;
			stack<char> right;
			temp = "";
			i++;
			left.push('(');
			while (i < c.size())
			{
				if (c.at(i) == '(') left.push('(');
				else if (c.at(i) == ')') right.push(')');
				if (left.size() >= right.size() && !left.empty() && !right.empty())
				{
					bool more_p = pop_stack(left, right);
					if (more_p) break;
					else check_arg = true;
				}
				temp = temp + c.at(i);
				i++;
			}
			if (!empty_stack(left, right))
			{
				cout << "Error: No matching '(' for ')'" << endl;
				return false;
			}
			if (empty_command(temp))
			{
				cout << "Error: Unexpected '(' or ')'" << endl;
				return false;
			}
			bool continue_on = true;
			if (check_arg && arg_error(temp))
			{
				temp = "QuynhNguyenIsAwesome";
				continue_on = false;
			}
			insert_command(temp);
			if (continue_on)
			{
				int start = for_connectors.find(temp);
				--start;
				int end = temp.size() + 2;
				for_connectors.replace(start, end, "C");
			}
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

void Rshell::parse_connectors(string command_line)
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

void Rshell::clear_queue()
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

//gets input from user and parses the information into the queues
void Rshell::prompt()
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

//pops the command pointer off the queue
void Rshell::ptr_pop()
{
	delete command_ptrs.front();
	command_ptrs.front() = 0;
	command_ptrs.pop();
}

//Goes through the command and connector queues
//returns true if there was no exit command
bool Rshell::fork_process()
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

//Returns whether or not the last command failed
bool Rshell::get_fail()
{
	return fail;
}

//main function to run rshell
bool Rshell::run_shell()
{
	while (run)
	{
		prompt();
		run = fork_process();
		clear_queue();
	}
	return true;
}
