#include "netlist_circuit.h"



netlist_circuit::netlist_circuit(string header) : netlist_context(header)
{
}


netlist_circuit::~netlist_circuit()
{
}


void netlist_circuit::parce()
{
	shared_ptr<element> element;
	for (size_t i = 0; i < context_.size(); i++) {
		if (context_[i][0] != '*') {
			element = element::parce(context_[i]);
			if (element) {
				elements_.push_back(element);
				comments_.push_back("");
			}
			else if (context_[i] == ""){
				elements_.push_back(NULL);
				comments_.push_back("");
			}
			else {
				comments_.push_back(context_[i]);
			}
		}
		else {
			comments_.push_back(context_[i]);
		}
	}
}