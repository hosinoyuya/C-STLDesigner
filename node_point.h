#pragma once
#include <string>
#include <regex>

using namespace std;

class node_point
{
public:
	node_point(string point = "", string node = "");
	~node_point();
	string node_;
	string print_name_;
	string prefix_;
private:
	void set_print_name(string point);
	regex reg_printname_;
};

