#pragma once
#include "node_point.h"
#include "line_length.h"
#include "char_impedance.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <regex>

using namespace std;

enum ELEMENT_TYPE {DEFAULT_ELEMENT, R_ELEMENT, T_ELEMENT, W_ELEMENT, X_ELEMENT, N_ELEMENT};

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
	virtual void set_nodes(vector<string> nodes);
	virtual void set_impedance(int impedance);
	virtual void set_length(double length);
	vector<shared_ptr<node_point>> nodes_;
	shared_ptr<line_length> length_;
	ELEMENT_TYPE type_;
	shared_ptr<char_impedance> impedance_;
	virtual string to_str();
	virtual string get_param_str() = 0;
private:
	static shared_ptr<element> generate(string name);
	bool is_node(string node);
	virtual void set_parameters(string key, string val) = 0;
};