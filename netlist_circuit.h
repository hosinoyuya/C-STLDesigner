#pragma once
#include "netlist_context.h"
class netlist_circuit :
	public netlist_context
{
public:
	netlist_circuit(string header = "");
	~netlist_circuit();
};

