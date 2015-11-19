#include "netlist_circuit.h"



netlist_circuit::netlist_circuit(string header) : netlist_context(header)
{
}


netlist_circuit::~netlist_circuit()
{
}


void netlist_circuit::parce()
{
	for (size_t i = 0; i < context_.size(); i++) {
		if (context_[i][0] != '*') {
			elements_.push_back(element::parce(context_[i]));
			comments_.push_back("");
		}
		else {
			comments_.push_back(context_[i]);
		}
	}
}