#include "line_length.h"

const regex REG_LENGTH(R"(l|L|len|LEN|Length|length|LENGTH)");

line_length::line_length(string key, string val)
{
	if (val != "") {
		
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
	val_ = unit_change::unit_decode(val);
}