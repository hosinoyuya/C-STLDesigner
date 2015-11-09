#pragma once
#include "stl_config.h"
#include "ga_opt.h"
#include <iostream>
#include <memory>

using namespace std;

class opt_runner
{
public:
	opt_runner(stl_config config, int seed);
	~opt_runner();
	void run();
private:
	stl_config config;
	int seed;
	std::shared_ptr<ga_opt> algorithm;
	void stl_initialize();
};

