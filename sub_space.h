#pragma once
#include "stl_config.h"
#include "element.h"
#include "telement.h"
#include "welement.h"
#include "xelement.h"
#include "nelement.h"
#include "line_length.h"
#include "stl_line.h"
#include "stl_random.h"
#include "length_utils.h"
#include <memory>
#include <regex>
#include <algorithm>
#include <numeric>

using namespace std;

class sub_space
{
public:
	sub_space(stl_config config);
	~sub_space();
	void set_element(shared_ptr<element> elem);
	void split();
	vector<shared_ptr<element>> segments_;
private:
	void set_config_parameters(stl_config config);
	int sub_offset_;
	int minimum_impedance_;
	int maximum_impedance_;
	int impedance_step_;
	double minimum_length_;
	double length_step_;
	shared_ptr<element> element_;
	vector<shared_ptr<node_point>> nodes_;
	void parse_name();
	int segment_num_;
	int index_;
	string first_name_;
	vector<double> get_random_segment_length(double min, double max, int segment_num);
	vector<int> get_random_segment_impedance(int imp_min, int imp_max, int imp_step, int segment_num);
	vector<string> get_segment_node(int index, int point_offset);
	vector<string> get_segment_node_core(vector<shared_ptr<node_point>> nodes, int input, int output);
	shared_ptr<element> get_segment_element(int index, vector<string> point, double segment_length, int segment_impedance);
};