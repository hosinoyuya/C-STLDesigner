#pragma once
#include "netlist_context.h"
#include <string>
#include <vector>
#include <iostream>

class netlist_commands :
	public netlist_context
{
public:
	netlist_commands();
	~netlist_commands();
private:
	vector<string> dummy_;
	vector<string> models_;
	vector<string> node_params_;
	vector<string> all_commands_;
};

