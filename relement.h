#pragma once
#include "element.h"
#include "unit_change.h"
#include <string>

using namespace std;

class relement : public element
{
public:
	relement(string name);
	~relement();
private:
	virtual void set_parameters(string key, string val);
	double value_;
};

