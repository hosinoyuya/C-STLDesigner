#include "telement.h"

const regex Z0(R"(Z0)", regex_constants::icase);
const regex TD(R"(TD)", regex_constants::icase);

telement::telement(string name) : line_element_base(name)
{
	time_delay_ = 0;
	type_ = T_ELEMENT;
	param_str_ = "";
}


telement::~telement()
{
}


int telement::node_num()
{
	return 4;
}


void telement::set_spetialized_parameters(string key, string val)
{
	if (regex_match(key, Z0)) {
		impedance_ = make_shared<char_impedance>(key, val);
	}
	if (regex_match(key, TD)) {
		time_delay_ = unit_change::unit_decode(val);
	}
}

void telement::set_length(double length)
{
	length_ = make_shared<line_length>(*length_);
	double old_length = length_->value_;
	length_->value_ = length;
	time_delay_ = time_delay_ * (length / old_length);
}


string telement::get_param_str() {
	return impedance_->to_str() + "\tTD=" + unit_change::unit_encode(time_delay_) + "\t$ " + length_->to_str();
}