#include "node_point.h"
#include <iostream>

const regex REG_PRINTNAME(R"((\w+)\((\w+)\))");

node_point::node_point(string point, string node)
{
	prefix_ = "";
	node_ = "";
	if (point != "" && node == "") {
		set_print_name(point);
	}
	else {
		node_ = node;
	}
}


node_point::~node_point()
{
}


void node_point::set_print_name(string point)
{
	print_name_ = point;
	smatch match;
	regex_search(print_name_, match, REG_PRINTNAME);
	prefix_ = match[1].str();
	node_ = match[2].str();
}