#pragma once
#include "netlist_circuit.h"
class stl_circuit :
	public netlist_circuit
{
public:
	stl_circuit(string header = "");
	~stl_circuit();
};

