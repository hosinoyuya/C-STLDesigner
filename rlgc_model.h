#pragma once
#include <string>
#include <vector>

using namespace std;

class rlgc_model
{
public:
	rlgc_model(string key, int netnum);
	~rlgc_model();
	void set_value(string val);
private:
	string key_;
	int net_num_;
	vector<string> values_;
};

