#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include "test.h"
using namespace std;

class Test
{
protected:
	string orig;
	bool bracket; //true if the command started with a [
	bool flag; //true if there was a "-" flag
	bool yes; //true if ran successfully
	vector<string> arg;
public: 
	Test(string o, string fw)
	{
		flag = false;
		orig = o;
		if (fw == "[") bracket = true;
		else bracket = false;
		yes = false;
		arg.clear();
		parse_orig();
	}
	void parse_orig()
	{
		char* token;
		char* store = strdup(orig.c_str());
		string temp;
		token = strtok(store, " ");
		while (token != NULL)
		{
			string a = token;
			temp = temp + " " + a;
			arg.push_back(a);
			token = strtok(NULL, " ");
		}
		orig = temp;
	}
	//returns false if failed
	bool run(struct stat& sb)
	{
		char* token;
		char* store = strdup(orig.c_str());
		int pos = 0;
		char* arr[10];
		token = strtok(store, " ");
		while (token != NULL)
		{
			arr[pos] = token;
			pos++;
			token = strtok(NULL, " ");
		}
		//if (bracket) --pos;
		arr[pos] = NULL;
		int i = 1;
		if (flag) i++;
		if (stat(arr[i], &sb) >= 0) return true;
		perror("stat");
		return false;

	}
	//returns false if it did not run successfully
	bool execute()
	{
		flag = false;
		struct stat sb;
		//Not enough arguments
		if (bracket && arg.size() < 3)
		{
			cout << "Error: Not enough arguments" << endl;
			return false;
		}
		if (!(bracket) && arg.size() < 2)
		{
			cout << "Error: Not enough arguments" << endl;
			return false;
		}
		//If there is no matching ] for [
		if (bracket)
		{
			if (orig.find("[") == string::npos && orig.find("]") == string::npos)
			{
				cout << "Error: No matching ']' for '['" << endl;
				return false;
			}
		}
		if (orig.find("[[") != string::npos || orig.find("]]") != string::npos)
		{
			cout << "Error: Unexpected '[' or ']'" << endl;
			return false;
		}
		//Too many arguments for bracket
		if (bracket && (arg.size() > 4 || arg.at(1).at(0) != '-'))
		{
			cout << "Error: Too many arguments" << endl;
			return false;
		}
		//Too many arguments for test
		if (!(bracket) && (arg.size() > 3 || arg.at(1).at(0) != '-'))
		{
			cout << "Error: Too many arguments" << endl;
			return false;
		}
		//If the only thing they enter is []
		if (arg.size() == 2 && arg.at(0) == "[" && arg.at(1) == "]")
		{
			cout << "Error: Empty []" << endl;
			return false;
		}
		//if the argument after test or [ isn't a flag
		if (arg.at(1).at(0) != '-')
		{
			yes = run(sb);
			if (yes) return true;
			return false;
		}
		else if (arg.at(1).at(0) == '-')
		{
			flag = true;
			if (arg.at(1) == "-") return false;
			else if (arg.at(1) == "-e")
			{
				if (!bracket && arg.size() == 2) return true;
				else if (bracket && arg.size() == 3) return true;
				else yes = run(sb);
				if (yes) return true;
				return false;
			}
			else if (arg.at(1) == "-f")
			{
				if (!bracket && arg.size() == 2) return true;
				else if (bracket && arg.size() == 3) return true;
				else yes = run(sb);
				if (yes && S_ISREG(sb.st_mode)) return true;
				return false;
			}
			else if (arg.at(1) == "-d")
			{
				if (!bracket && arg.size() == 2) return true;
				else if (bracket && arg.size() == 3) return true;
				else yes = run(sb);
				if (yes && S_ISDIR(sb.st_mode)) return true;
				return false;
			}
			else
			{
				cout << "Invalid Flag: For the sake of this assignment, please use -e, -f, or -d" << endl;
				return false;
			}
		}
		return true;
	}
};

#endif