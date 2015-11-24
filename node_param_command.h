#pragma once
#include "command_base.h"
#include <string>

using namespace std;

class node_param_command :
	public command_base
{
public:
	node_param_command();
	~node_param_command();
	virtual void set_parameters(string line);
	virtual string to_str();
private:
	string line_;
};

