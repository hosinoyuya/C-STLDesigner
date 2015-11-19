#pragma once
#include "line_element_base.h"
#include <string>

using namespace std;

class xelement : public line_element_base
{
public:
	xelement(string name);
	~xelement();
};

