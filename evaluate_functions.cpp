#include "evaluate_functions.h"



evaluate_functions::evaluate_functions()
{
}


evaluate_functions::~evaluate_functions()
{
}


double evaluate_functions::calc_integral(double time_interval, vector<double> &voltage1, vector<double> &voltage2)
{
	double diff1, diff2;
	double score = 0;
	for (size_t i = 0; i < voltage1.size()-1; i++) {
		diff1 = fabs(voltage2[i] - voltage1[i]);
		diff2 = fabs(voltage2[i+1] - voltage1[i+1]);
		score += (diff1 + diff2) * time_interval / 2.0;
	}
	return score;
}