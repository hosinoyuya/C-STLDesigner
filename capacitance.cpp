#include "capacitance.h"

const regex REG_CAPACITANCE_VALUE(R"(C|c|capacitance|CAPACITANCE)");

capacitance::capacitance(string key, string val)
{
	key_ = "";
	if (val != "") {
		set_parameters(key, val);
	}
}


capacitance::~capacitance()
{
}


bool capacitance::is_key(string key)
{
	return regex_match(key, REG_CAPACITANCE_VALUE);
}


void capacitance::set_parameters(string key, string val)
{
	key_ = key;
	value_ = unit_change::unit_decode(val);
}


string capacitance::to_str()
{
	return key_ + "=" + unit_change::unit_encode(value_);
}
