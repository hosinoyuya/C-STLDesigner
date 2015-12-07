#include "line_length.h"

const regex REG_LENGTH(R"(l|L|len|LEN|Length|length|LENGTH)");

line_length::line_length(string key, string val)
{
	key_ = "";
	if (val != "") {
		set_parameters(key, val);
	}
}


line_length::~line_length()
{
}


bool line_length::is_key(string key)
{
	return regex_match(key, REG_LENGTH);
}


void line_length::set_parameters(string key, string val)
{
	key_ = key;
	value_ = unit_change::unit_decode(val);
}


string line_length::to_str()
{
	return key_ + "=" + unit_change::unit_encode(value_);
}