#pragma once
#include <string>

using namespace std;

class command_base
{
public:
	command_base();
	~command_base();
	virtual string to_str() = 0;
	virtual void set_parameters(string line) = 0;
};

