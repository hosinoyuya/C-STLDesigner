#pragma once
#include "unit_change.h"
#include <string>
#include <vector>

using namespace std;

class rlgc_model
{
public:
	rlgc_model(string key, int netnum);
	~rlgc_model();
	void set_value(double val);
	string to_str();
private:
	string key_;
	int net_num_;
	vector<double> values_;
};

