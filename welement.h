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
private:
	virtual void set_spetialized_parameters(string key, string val);
	shared_ptr<char_impedance> impedance;
};

