#pragma once
#include "command_base.h"
#include <string>

using namespace std;

class dummy_command :
	public command_base
{
public:
	dummy_command();
	~dummy_command();
	virtual void set_parameters(string line);
	virtual string to_str();
private:
	string line_;
};

