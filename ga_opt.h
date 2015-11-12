#pragma once
#include "stl_config.h"

class ga_opt
{
public:
	ga_opt(stl_config config, int seed);
	~ga_opt();
private:
	stl_config config_;
	int seed_;
public:
	void run();
};

