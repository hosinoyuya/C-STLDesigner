#pragma once
#include "netlist_context.h"
class netlist_scores :
	public netlist_context
{
public:
	netlist_scores();
	~netlist_scores();
	virtual string to_str();
};

