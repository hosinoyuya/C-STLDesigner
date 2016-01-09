#pragma once
#include "crossover_base.h"
class one_point_crossover :
	public crossover_base
{
public:
	one_point_crossover(stl_config config);
	~one_point_crossover();
	virtual vector<shared_ptr<stl>> crossover(int generation, int offspring_num, shared_ptr<stl> parent1, shared_ptr<stl> parent2);
private:
	void crossover_subspace(shared_ptr<sub_space> parent1, shared_ptr<sub_space> parent2,
		shared_ptr<sub_space> new_space1, shared_ptr<sub_space> new_space2);
};

