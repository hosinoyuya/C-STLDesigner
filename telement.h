#pragma once
#include "line_element_base.h"
#include "unit_change.h"
#include <string>

using namespace std;

class telement : public line_element_base
{
public:
	telement(string name);
	~telement();
	virtual string get_param_str();
private:
	double time_delay_;
	virtual int node_num();
	virtual void set_spetialized_parameters(string key, string val);
	string param_str_;
	bool first_param_;
};

