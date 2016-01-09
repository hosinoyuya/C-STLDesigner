#pragma once
#include "stl_config.h"
#include "stl.h"
#include <memory>

using namespace std;

class crossover_base
{
public:
	crossover_base(stl_config config);
	~crossover_base();
	virtual vector<shared_ptr<stl>> crossover(int generation, int offspring_num, shared_ptr<stl> parent1, shared_ptr<stl> parent2) = 0;
protected:
	stl_config config_;
	vector<double> ajust_small_segment(vector<double> lengths, double ajust_length);
	vector<double> ajust_length(vector<double> lengths, double ajust_length);
};

