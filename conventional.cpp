#include "conventional.h"

shared_ptr<simulator> conventional::simulator_;
shared_ptr<netlist_base> conventional::netlist_;

conventional::conventional()
{
}


conventional::~conventional()
{
}


void conventional::set_simulator(shared_ptr<simulator> simulator)
{
	simulator_ = simulator;
}


void conventional::set_template(std::shared_ptr<netlist_base> netlist)
{
	netlist_ = netlist;
}