#pragma once
#include "netlist_context.h"
#include <string>
#include <vector>
#include <iostream>

class netlist_comands :
	public netlist_context
{
public:
	netlist_comands();
	~netlist_comands();
private:
	const string REG_CONTEXT_MARKER = "\*\*\*(.*)\*\*\* -+\*";
	const string REG_CONTEXT_END = "\*-+\*";
	vector<string> dummy_;
	vector<string> models_;
	vector<string> node_params_;
	vector<string> all_commands_;
};

