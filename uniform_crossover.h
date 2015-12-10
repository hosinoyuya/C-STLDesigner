#pragma once
#include "stl_config.h"
#include "stl.h"
#include "sub_space.h"
#include "element.h"
#include "stl_random.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class uniform_crossover
{
public:
	uniform_crossover(stl_config config);
	~uniform_crossover();
	vector<shared_ptr<stl>> crossover(int generation, int offspring_num, shared_ptr<stl> parent1, shared_ptr<stl> parent2);
private:
	stl_config config_;
	void crossover_subspace(shared_ptr<sub_space> parent1, shared_ptr<sub_space> parent2,
		shared_ptr<sub_space> new_space1, shared_ptr<sub_space> new_space2);
	vector<double> ajust_length(vector<double> lengths, double ajust_length);
};

