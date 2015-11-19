#pragma once
#include "line_element_base.h"
#include <string>

using namespace std;

class telement : public line_element_base
{
public:
	telement(string name);
	~telement();
private:
	double time_delay_;
	virtual int node_num();
	virtual void set_spetialized_parameters(string key, string val);
};

