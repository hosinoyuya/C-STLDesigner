#include "simulator.h"

#include <iostream>

using namespace std;

simulator::simulator(stl_config config)
{
	config_ = config;
}


simulator::~simulator()
{
}


void simulator::run(string filepath, string command)
{
	cout << filepath << endl;
	cout << command << endl;
}
