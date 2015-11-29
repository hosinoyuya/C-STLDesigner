#pragma once
#include "node_point.h"
#include <memory>
#include <vector>

using namespace std;

class transient_wave
{
public:
	transient_wave(shared_ptr<node_point> point);
	~transient_wave();
	vector<double> time_division_;
	vector<double> voltage_;
	double time_begin_;
	double time_end_;
	double time_interval_;
	size_t size();
	void generate_time_division(vector<double> time_dividion);
private:
	shared_ptr<node_point> point_;
};

