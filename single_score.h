#pragma once
#include "point_score.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

class single_score
{
public:
	single_score();
	~single_score();
	void set(vector<shared_ptr<point_score>> point_scores);
	string to_str();
	void calc_ratio(shared_ptr<single_score> divisor);
	vector<shared_ptr<point_score>> point_scores_;
private:
	double value_;
	string to_spice_comment();
	shared_ptr<point_score> get_divisor(string point, vector<shared_ptr<point_score>> divisors);
};

