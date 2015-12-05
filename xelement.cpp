#include "xelement.h"



xelement::xelement(string name) : line_element_base(name)
{
	type_ = X_ELEMENT;
}


xelement::~xelement()
{
}


void xelement::set_spetialized_parameters(string key, string val)
{
}