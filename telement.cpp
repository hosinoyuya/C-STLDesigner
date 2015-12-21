#include "telement.h"



telement::telement(string name) : line_element_base(name)
{
	time_delay_ = 0;
	type_ = T_ELEMENT;
	param_str_ = "";
	first_param_ = true;
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
	if (first_param_) {
		first_param_ = false;
	}
	else {
		param_str_ += " ";
	}
	param_str_ += key + "=" + val;
}


string telement::get_param_str() {
	return param_str_;
}