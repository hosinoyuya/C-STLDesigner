#pragma once
#include "command_base.h"
#include "unit_change.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class tran_command :
	public command_base
{
public:
	tran_command();
	~tran_command();
	virtual void set_parameters(string line);
	virtual string to_str();
	string resolution_;
	string end_time_;
	string start_time_;
private:
	string key_;
};
