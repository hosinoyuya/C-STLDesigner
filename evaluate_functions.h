#pragma once
#include <vector>
#include <string>
#include <math.h>
#include <memory>
#include "point_score.h"

using namespace std;

class evaluate_functions
{
public:
	evaluate_functions();
	~evaluate_functions();
	static void calc_integral(double time_interval, vector<double> &voltage1, vector<double> &voltage2,
		shared_ptr<point_score> &p_score);
	static void calc_fitting_integral(double time_interval, double shift_ratio,
		vector<double> &voltage1, vector<double> &voltage2, shared_ptr<point_score> &p_score);
};

