#pragma once
#include "element.h"
#include "capacitance.h"
#include "unit_change.h"
#include <string>
#include <memory>
#include <regex>

using namespace std;

class celement : public element
{
public:
	celement(string name);
	~celement();
	virtual string get_param_str();
private:
	virtual int node_num();
	virtual void set_parameters(string key, string val);
	double value_;
};

