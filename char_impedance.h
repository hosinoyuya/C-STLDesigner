#pragma once
#include <string>
#include <regex>

using namespace std;

class char_impedance
{
public:
	char_impedance(string key, string val);
	~char_impedance();
private:
	virtual void set_parameters(string key, string val);
	string key_;
	string value_prefix_;
	string value_;
};

