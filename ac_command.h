#pragma once
#include "command_base.h"
#include <string>

using namespace std;

class ac_command :
	public command_base
{
public:
	ac_command();
	~ac_command();
	virtual void set_parameters(string line);
	virtual string to_str();
private:
	string line_;
};

