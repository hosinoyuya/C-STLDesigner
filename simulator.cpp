#include "simulator.h"



simulator::simulator(stl_config config)
{
	config_ = config;
	name_ = config.spice_name_;
}


simulator::~simulator()
{
}


int simulator::run(string command)
{
	int ret = system(command.c_str());
	if (ret != 0) {
		cerr << "simulator exception occured." << endl;
	}
    return ret;
}
