#pragma once
#include "line_element_base.h"
#include "char_impedance.h"
#include <string>
#include <memory>
#include <regex>

using namespace std;

class welement : public line_element_base
{
public:
	welement(string name);
	~welement();
	virtual string get_param_str();
private:
	virtual void set_spetialized_parameters(string key, string val);
};

