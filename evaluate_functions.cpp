#include "evaluate_functions.h"



evaluate_functions::evaluate_functions()
{
}


evaluate_functions::~evaluate_functions()
{
}


void evaluate_functions::calc_integral(double time_interval, vector<double> &voltage1, vector<double> &voltage2,
	shared_ptr<point_score> &p_score)
{
	double diff1, diff2;
	double score = 0;
	for (size_t i = 0; i < voltage1.size()-1; i++) {
		diff1 = fabs(voltage2[i] - voltage1[i]);
		diff2 = fabs(voltage2[i+1] - voltage1[i+1]);
		score += (diff1 + diff2) * time_interval / 2.0;
	}
	p_score->set(score);
}


void evaluate_functions::calc_fitting_integral(double time_interval, double shift_ratio,
	vector<double> &voltage1, vector<double> &voltage2, shared_ptr<point_score> &p_score)
{
	double diff1, diff2;
	double score, min_score = numeric_limits<size_t>::max();
	size_t shift_num = voltage1.size() * shift_ratio;
	size_t shift;
	for (size_t i = 0; i < shift_num; i++) {
		score = 0;
		for (size_t j = 0; j < voltage1.size() - 1; j++) {
			diff1 = fabs(voltage2[(j + i) % voltage1.size()] - voltage1[j]);
			diff2 = fabs(voltage2[(j + i + 1) % voltage1.size()] - voltage1[j+1]);
			score += (diff1 + diff2) * time_interval / 2.0;
		}
		if (min_score > score) {
			min_score = score;
			shift = i;
		}
	}

	p_score->set(min_score);
	p_score->shift_ = (double)shift / (double)voltage1.size();
}