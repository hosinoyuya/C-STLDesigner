#include "telement.h"



telement::telement(string name) : line_element_base(name)
{
	time_delay_ = 0;
	type_ = T_ELEMENT;
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

}


string telement::get_param_str() {
	return "";
}