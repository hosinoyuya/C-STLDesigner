#include "netlist_context.h"



netlist_context::netlist_context(string header)
{
	if (header != "") {
		header_ = header;
	}
	else {
		header_ = "*** *** -------------------------------------------------------------*\n";
	}
}


netlist_context::~netlist_context()
{
}


void netlist_context::operator<<(string line)
{
	context_.push_back(line);
}


void netlist_context::parce()
{
	for (size_t i = 0; i < context_.size(); i++) {
		contents_.push_back(context_[i]);
	}
}
