#pragma once
#include "stl_config.h"
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;

class simulator
{
public:
	simulator(stl_config config);
	~simulator();
	virtual bool simulate(string file_path) = 0;
	string name_;
protected:
	static int run(string command);
	stl_config config_;
};

