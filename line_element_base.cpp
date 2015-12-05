#include "line_element_base.h"



line_element_base::line_element_base(string name) : element(name)
{
}


line_element_base::~line_element_base()
{
}


int line_element_base::node_num()
{
	return 4;
}


void line_element_base::set_parameters(string key, string val)
{
	set_spetialized_parameters(key, val);
	
	if (line_length::is_key(key)) {
		length_ = make_shared<line_length>(key, val);
	}
}