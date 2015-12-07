#include "relement.h"



relement::relement(string name) : element(name)
{
	type_ = R_ELEMENT;
}


relement::~relement()
{
}


void relement::set_parameters(string key, string val)
{
	if (key != "") {
		cerr << "key is not defined!" << endl;
		exit(0);
	}
	value_ = unit_change::unit_decode(val);
}


string relement::get_param_str()
{
	return to_string(value_);
}