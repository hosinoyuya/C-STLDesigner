#include "node_point.h"

#include <iostream>

node_point::node_point(string point, string node)
{
	reg_printname_ = R"((\w+)\((\w+)\))";
	if (point == "") {
		set_print_name(point);
	}
	node_ = node;
}


node_point::~node_point()
{
}


void node_point::set_print_name(string point)
{
	print_name_ = point;
	smatch match;
	regex_search(print_name_, match, reg_printname_);
	prefix_ = match[1].str();
	node_ = match[2].str();
	//cout << match[1].str() << " " << match[2].str() << endl;
}