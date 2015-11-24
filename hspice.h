#pragma once
#include "simulator.h"
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

class hspice :
	public simulator
{
public:
	hspice(stl_config config);
	~hspice();
	virtual void simulate(string file_path);
};

