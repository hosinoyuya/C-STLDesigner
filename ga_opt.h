#pragma once
#include "stl_config.h"
#include "stl.h"
#include <iostream>
#include <memory>

using namespace std;

class ga_opt
{
public:
	ga_opt(stl_config config, int seed);
	~ga_opt();
	void run();
private:
	stl_config config_;
	int seed_;
	void generate_random_stl();
};

