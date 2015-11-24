#pragma once
#include "command_base.h"
#include "node_point.h"
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <memory>

using namespace std;

class print_command :
	public command_base
{
public:
	print_command();
	~print_command();
	virtual void set_parameters(string line);
	virtual string to_str();
private:
	string key_;
	vector<shared_ptr<node_point>> nodes_;
};

