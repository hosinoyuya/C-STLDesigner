#pragma once
#include "stl_config.h"
#include "stl.h"
#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

class ga_opt
{
public:
	ga_opt(stl_config config, int seed);
	~ga_opt();
	void run();
private:
	void generate_random_stl();
	shared_ptr<stl> select_best();
	vector<shared_ptr<stl>> population_;
	stl_config config_;
	int seed_;
};

