#pragma once
#include "uniform_crossover.h"
#include "blx_crossover.h"
#include "one_point_crossover.h"
#include "stl_config.h"
#include "stl.h"
#include "stl_random.h"
#include "stl_signal.h"
#include "hspice.h"
#include <memory>
#include <vector>
#include <float.h>

using namespace std;

class normal_ga
{
public:
	normal_ga(stl_config config);
	~normal_ga();
	virtual void clear();
	virtual void change(int generation, vector<shared_ptr<stl>>& population);
protected:
	shared_ptr<crossover_base> crossover_;
	shared_ptr<stl> get_roulet_member(vector<shared_ptr<stl>> population,
		shared_ptr<stl> eliminate_member = NULL);
	double value_to_score(double value);
};

