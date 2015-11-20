#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <stdlib.h>
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
	bool bracket;
	bool yes;
	vector<string> arg;
public: 
	Test(string o, string fw)
	{
		orig = o;
		if (fw == "[") bracket = true;
		else bracket = false;
		yes = false;
	}
	void parse_orig()
	{
		char* token;
		char* store = strdup(orig.c_str());
		string temp;
		token = strtok(store, " ");
		string a;
		while (token != NULL)
		{
			a = token;
			temp = temp + " " + a;
			arg.push_back(a);
			token = strtok(NULL, " ");
		}
		orig = temp;
	}

	bool run(struct stat& sb)
	{

		char* token;
		char* store = strdup(orig.c_str());
		int pos = 0;
		char* arr[10];
		token = strtok(store, " ");
		bool bracket = false;
		while (token != NULL)
		{
			arr[pos] = token;
			pos++;
			token = strtok(NULL, " ");
		}
		if (bracket) --pos;
		arr[pos] = NULL;
		if (stat(arr[1], &sb) >= 0) return true;
		else return false;

	}
	//returns false if it did not run successfully
	bool execute()
	{
		struct stat sb;
		if (arg.size() != 2)
		{
			cout << "Error: Not Enough Arguments" << endl;
			return false;
		}
		if (arg.size() == 2 && arg.at(0) == "[" && arg.at(1) == "]")
		{
			cout << "Error: Empty []" << endl;
			return false;
		}
		
		if (arg.at(1).at(0) != '-' && arg.size() == 2)
		{
			yes = run(sb);
			if (yes) return true;
			return false;
		}
		else if (arg.at(1).at(0) == '-')
		{
			if (arg.at(1) == "-") return false;
			else if (arg.at(1) == "-e")
			{
				if (arg.size() == 2) return true;
				else yes = run(sb);
				if (yes) return true;
				return false;
			}
			else if (arg.at(1) == "-f")
			{
				if (arg.size() == 2) return true;
				else yes = run(sb);
				if (yes && S_ISREG(sb.st_mode)) return true;
				return false;
			}
			else if (arg.at(1) == "-d")
			{
				if (arg.size() == 2) return true;
				else yes = run(sb);
				if (yes && S_ISDIR(sb.st_mode)) return true;
				return false;
			}
			else
			{
				cout << "Error: Invalid tag. Please use -e, -f, or -d" << endl;
				return false;
			}
		}
	}
};

#endif