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
