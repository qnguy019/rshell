//#include "shell.h"
#include "command.h"

//constructor
Subshell::Subshell(string command)
{
	command_line = command;
	fail = false;
}

//returns whether or not the last command failed
bool Subshell::get_fail()
{
	return fail;
}

//returns false if there is no command in between the ()
bool Subshell::check_paren_empty(string command_line)
{
	return true;
}

//return false if there is a ( or ) in a command
bool Subshell::check_paren_in_commands(string temp)
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

void Subshell::insert_command(string c)
{
	Command* new_comm = new Command(c);
	command_ptrs.push(new_comm);
}

//returns true if the command was empty
bool Subshell::empty_command(string temp)
{
	char* store = strdup(temp.c_str());
	char* token = strtok(store, " ");
	if (token == NULL) return true;
	return false;
}

//return true if we found matching parenthesis
bool Subshell::empty_stack(stack<char> l, stack<char> r)
{
	if (l.size() == r.size()) return true;
	return false;
}

//pops the '(' and ')' off their respective stack. 
bool Subshell::pop_stack(stack<char> &l, stack<char> &r)
{
	l.pop();
	r.pop();
	return (empty_stack(l, r));
}

//returns true if there was only one argument in (( ))
bool Subshell::arg_error(string c)
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
bool Subshell::parse_pointers()
{
	bool check_arg = false;
	string temp;
	string c = command_line;
	string for_connectors = c;
	for (unsigned i = 0; i < c.size(); i++)
	{
		if (c.at(i) == '(')
		{
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
				temp = "";
			}
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
	command_line = for_connectors;
	return true;

}

void Subshell::parse_connectors()
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

void Subshell::clear_queue()
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
void Subshell::prompt()
{
	if (command_line == "" || command_line.at(0) == '#') return;
	if (parse_pointers() == false) return;
	parse_connectors();
}

//pops the command pointer off the queue
void Subshell::ptr_pop()
{
	delete command_ptrs.front();
	command_ptrs.front() = 0;
	command_ptrs.pop();
}

//Goes through the command and connector queues
//returns true if there was no exit command
bool Subshell::fork_process()
{
	while (!command_ptrs.empty())
	{
		if (command_ptrs.front()->execute() == false) return false;
		fail = command_ptrs.front()->get_fail_command();
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

//main function to run subshell
bool Subshell::run_shell()
{
	prompt();
	bool run = fork_process();
	clear_queue();
	return run;
}