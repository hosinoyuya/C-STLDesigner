#pragma once
#include "line_element_base.h"
#include <string>

using namespace std;

class nelement : public line_element_base
{
public:
	nelement(string name);
	~nelement();
private:
	virtual void set_spetialized_parameters(string key, string val);
};

