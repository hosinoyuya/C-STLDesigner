#include "hspice.h"



hspice::hspice(stl_config config) : simulator(config)
{
}


hspice::~hspice()
{
}


void hspice::simulate(string file_path) {
	string command = "hspice -C " + file_path + " -o " + 
		boost::algorithm::replace_all_copy(file_path, config_.netlist_extension_, "");
	simulator::run(file_path, command);
}