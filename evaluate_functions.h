#pragma once
#include <vector>
#include <string>

using namespace std;

class evaluate_functions
{
public:
	evaluate_functions();
	~evaluate_functions();
	static double calc_integral(vector<string> time_interval, vector<string> voltage1, vector<string> voltage2);
};

