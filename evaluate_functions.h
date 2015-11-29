#pragma once
#include <vector>
#include <string>

using namespace std;

class evaluate_functions
{
public:
	evaluate_functions();
	~evaluate_functions();
	static double calc_integral(double time_interval, vector<double> &voltage1, vector<double> &voltage2);
};

