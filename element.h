#pragma once
#include "node_point.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <regex>

using namespace std;

class element
{
public:
	element(string name);
	~element();
	static shared_ptr<element> parce(string line);
	void set_node(vector<string> items);
	void set_parameters(vector<string> items);
protected:
	string name_;
private:
	static shared_ptr<element> generate(string name);
	virtual int node_num();
	bool is_node(string node);
	regex reg_node_;
	vector<shared_ptr<node_point>> nodes_;
};

