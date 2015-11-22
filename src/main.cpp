#include <iostream>
#include "command.h"

using namespace std;

int main()
{
	Shell* myshell = new Rshell();
	myshell->run_shell();
}