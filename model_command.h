#pragma once
#include "command_base.h"
#include "rlgc_model.h"
#include "unit_change.h"
#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <regex>
#include <memory>

using namespace std;

class model_command :
	public command_base
{
public:
	model_command();
	~model_command();
	virtual void set_parameters(string line);
	virtual string to_str();
private:
	void set_rlgc(vector<string> items);
	string key_;
	string name_;
	string element_;
	string type_;
	int net_num_;
	shared_ptr<rlgc_model> r_;
	shared_ptr<rlgc_model> l_;
	shared_ptr<rlgc_model> g_;
	shared_ptr<rlgc_model> c_;
	vector<shared_ptr<rlgc_model>> rlgc_models_;
};

