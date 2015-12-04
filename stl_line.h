#pragma once
#include "element.h"
#include <string>
#include <memory>
#include <regex>

using namespace std;

class stl_line
{
public:
	stl_line();
	~stl_line();
	static bool is_stl_element(shared_ptr<element> elem);
	static bool length_zero(double length);
	static const double EPSILON;
};

