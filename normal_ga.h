#pragma once
#include "uniform_crossover.h"
#include "blx_crossover.h"
#include "stl_config.h"
#include "stl.h"
#include "stl_random.h"
#include <memory>
#include <vector>

using namespace std;

class normal_ga
{
public:
	normal_ga(stl_config config);
	~normal_ga();
	void clear();
	void change(int generation, vector<shared_ptr<stl>>& population);
private:
	shared_ptr<stl> get_roulet_member(vector<shared_ptr<stl>> population, shared_ptr<stl> eliminate_member = NULL);
	shared_ptr<crossover_base> crossover_;
};

