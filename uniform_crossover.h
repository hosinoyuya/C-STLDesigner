#pragma once
#include "crossover_base.h"
#include "stl_config.h"
#include "stl.h"
#include "sub_space.h"
#include "element.h"
#include "stl_random.h"
#include "length_utils.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class uniform_crossover
	: public crossover_base
{
public:
	uniform_crossover(stl_config config);
	~uniform_crossover();
	virtual vector<shared_ptr<stl>> crossover(int generation, int offspring_num, shared_ptr<stl> parent1, shared_ptr<stl> parent2);
private:
	void crossover_subspace(shared_ptr<sub_space> parent1, shared_ptr<sub_space> parent2,
		shared_ptr<sub_space> new_space1, shared_ptr<sub_space> new_space2);
};

