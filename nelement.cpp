#include "nelement.h"



nelement::nelement(string name) : line_element_base(name)
{
	type_ = N_ELEMENT;
}


nelement::~nelement()
{
}


void nelement::set_spetialized_parameters(string key, string val)
{
}


string nelement::get_param_str() {
	return "";
}