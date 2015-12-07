#pragma once
#include "unit_change.h"
#include <regex>
#include <string>

using namespace std;

class line_length
{
public:
	line_length(string key, string val);
	~line_length();
	static bool is_key(string key);
	string to_str();
	string key_;
	double value_;
private:
	void set_parameters(string key, string val);
};

