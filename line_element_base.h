#pragma once
#include "element.h"
#include "line_length.h"
#include "capacitance.h"
#include <string>
#include <regex>

using namespace std;

class line_element_base :
	public element
{
public:
	line_element_base(string name);
	~line_element_base();
	virtual int node_num();
	virtual string get_param_str() = 0;
	int net_num_;
private:
	virtual void set_parameters(string key, string val);
	virtual void set_spetialized_parameters(string key, string val) = 0;
};
