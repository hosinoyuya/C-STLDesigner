#pragma once
#include "node_point.h"
#include "line_length.h"
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
	void set_node(vector<string> &items);
	void separate_parameters(vector<string> items);
	string name_;
	virtual int node_num();
	vector<shared_ptr<node_point>> nodes_;
	shared_ptr<line_length> length_;
private:
	static shared_ptr<element> generate(string name);
	bool is_node(string node);
	virtual void set_parameters(string key, string val) = 0;
};

