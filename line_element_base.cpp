#include "line_element_base.h"

const regex REG_N(R"(N)");

line_element_base::line_element_base(string name) : element(name)
{
	net_num_ = 1;
}


line_element_base::~line_element_base()
{
}


int line_element_base::node_num()
{
	return 4;
}


void line_element_base::set_impedance(int impedance)
{
	impedance_ = make_shared<char_impedance>(*impedance_);
	impedance_->value_ = impedance;
}


void line_element_base::set_length(double length)
{
	length_ = make_shared<line_length>(*length_);
	length_->value_ = length;
}

void line_element_base::set_parameters(string key, string val)
{
	set_spetialized_parameters(key, val);
	
	if (regex_match(key, REG_N)) {
		net_num_ = stoi(val);
	}

	if (line_length::is_key(key)) {
		length_ = make_shared<line_length>(key, val);
	}
}