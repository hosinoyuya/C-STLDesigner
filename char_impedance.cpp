#include "char_impedance.h"

const regex REG_IMPEDANCE_VALUE(R"(([A-z]*)([0-9]+))");

char_impedance::char_impedance(string key, string val)
{
	set_parameters(key, val);
}


char_impedance::~char_impedance()
{
}


void char_impedance::set_parameters(string key, string val)
{
	if (val == "") {
		return;
	}
	key_ = key;
	smatch match;
	regex_search(val, match, REG_IMPEDANCE_VALUE);
	value_prefix_ = match[1].str();
	value_ = stoi(match[2].str());
}