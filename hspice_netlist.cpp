#include "hspice_netlist.h"



hspice_netlist::hspice_netlist(string extention, vector<string> spice_extentions, vector<string> spice_extensions_nouse)
	: netlist_base(extention, spice_extentions, spice_extensions_nouse)
{
}


hspice_netlist::~hspice_netlist()
{
}
