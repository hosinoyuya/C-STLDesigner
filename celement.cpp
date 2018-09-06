#include "celement.h"


celement::celement(string name) : element(name)
{
	type_ = C_ELEMENT;
}


celement::~celement()
{
}


int celement::node_num()
{
	return 2;
}

void celement::set_parameters(string key, string val)
{
	if (key != "") {
		capacitance_ = make_shared<capacitance>(key, val);
	}
	else {
		cerr << "key is not defined!" << endl;
		exit(0);
	}
	
}


string celement::get_param_str()
{
	return capacitance_->to_str();
}