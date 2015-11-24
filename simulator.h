#pragma once
#include "stl_config.h"
#include <string>

using namespace std;

class simulator
{
public:
	simulator(stl_config config);
	~simulator();
	virtual void simulate(string file_path) = 0;
protected:
	void run(string filepath, string command);
	stl_config config_;
};

