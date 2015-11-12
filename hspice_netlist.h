#pragma once
#include "netlist_base.h"
#include "netlist_comands.h"

class hspice_netlist :
	public netlist_base
{
public:
	hspice_netlist(string extention, vector<string> spice_extentions, vector<string> spice_extensions_nouse);
	~hspice_netlist();
private:
	netlist_comands comands;
};

