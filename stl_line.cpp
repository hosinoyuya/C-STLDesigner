#include "stl_line.h"

const regex REG_STL(R"(.*_STL_.*)", regex_constants::icase);
const double stl_line::EPSILON = 1.0e-9;

stl_line::stl_line()
{
}


stl_line::~stl_line()
{
}


bool stl_line::is_stl_element(shared_ptr<element> elem)
{
	return regex_match(elem->name_, REG_STL);
}


bool stl_line::length_zero(double length)
{
	return length <= fabs(EPSILON);
}