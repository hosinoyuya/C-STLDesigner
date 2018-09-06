#pragma once
#include "unit_change.h"
#include <regex>
#include <string>

using namespace std;

class capacitance
{
public:
	capacitance(string key, string val);
	~capacitance();
	static bool is_key(string key);
	string to_str();
	string key_;
	double value_;
private:
	void set_parameters(string key, string val);
};

