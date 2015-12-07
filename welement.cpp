#include "welement.h"

const regex REG_RGCMODEL(R"(RLGCMODEL)", regex_constants::icase);

welement::welement(string name) : line_element_base(name)
{
	type_ = W_ELEMENT;
}


welement::~welement()
{
}


void welement::set_spetialized_parameters(string key, string val)
{
	if (regex_match(key, REG_RGCMODEL)) {
		impedance_ = make_shared<char_impedance>(key, val);
	}
}


string welement::get_param_str() {
	return impedance_->to_str() + "\t" + length_->to_str();
}