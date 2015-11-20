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
#include <sys/wait.h>
#include <unistd.h>
#include "test.h"
using namespace std;

class Test
{
protected:
	string orig;
	bool fail;

public: 
	Test(string a)
	{
		orig = a;
		fail = false;
	}
};

#endif