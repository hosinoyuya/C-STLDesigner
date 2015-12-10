#pragma once
#include "stl_config.h"
#include "stl.h"
#include "normal_ga.h"
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
	void loop_ga();
	shared_ptr<stl> select_best();
	void log_generation(shared_ptr<stl> best);
	vector<shared_ptr<stl>> population_;
	stl_config config_;
	int seed_;
};