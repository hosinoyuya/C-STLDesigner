#include "welement.h"

const regex REG_RGCMODEL(R"(RLGCMODEL)", regex_constants::icase);

welement::welement(string name) : line_element_base(name)
{
}


welement::~welement()
{
}


void welement::set_spetialized_parameters(string key, string val)
{
	if (regex_match(key, REG_RGCMODEL)) {
		impedance = make_shared<char_impedance>(key, val);
	}
}