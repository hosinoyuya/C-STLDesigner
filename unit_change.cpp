#include "unit_change.h"

const regex NUM(R"(\d+)");

const string CENTI = "c";
const string MILLI = "m";
const string MICRO = "u";
const string NANO = "n";
const string PICO = "p";
const string FEMTO = "f";
const string ATTO = "a";
const string ZEPTO = "z";
const string YOCTO = "y";

unit_change::unit_change()
{
}


unit_change::~unit_change()
{
}


double unit_change::unit_decode(string str)
{
	if (regex_match(str, NUM) || str == "") {
		return stod(str);
	}

	regex unit;
	smatch m;
	unit = CENTI;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		return stod(regex_replace(str, unit, "e-2"));
	}
	unit = MILLI;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		return stod(regex_replace(str, unit, "e-3"));
	}
	unit = MICRO;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		return stod(regex_replace(str, unit, "e-6"));
	}
	unit = NANO;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		return stod(regex_replace(str, unit, "e-9"));
	}
	unit = PICO;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		return stod(regex_replace(str, unit, "e-12"));
	}
	unit = FEMTO;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		return stod(regex_replace(str, unit, "e-15"));
	}
	unit = ATTO;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		// regex_replace(str, ATTO, "e-18");
		return 0.0;
	}
	unit = ZEPTO;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		// regex_replace(str, ZEPTO, "e-21");
		return 0.0;
	}
	unit = YOCTO;
	regex_search(str, m, unit);
	if (m.size() > 0) {
		// regex_replace(str, ATTO, "e-24");
		return 0.0;
	}

	return stod(str);
}


string unit_change::unit_encode(double num)
{
	string unit;
	if (num >= 0.001) {
		num *= 1000;
		unit = MILLI;
	}
	else if (num >= 0.000001) {
		num *= 1000000;
		unit = MICRO;
	}
	else if (num >= 0.000000001) {
		num *= 1000000000;
		unit = NANO;
	}
	else if (num >= 0.000000000001) {
		num *= 1000000000000;
		unit = PICO;
	}
	else if (num >= 0.000000000000001) {
		num *= 1000000000000000;
		unit = FEMTO;
	}
	else {
		num = 0;
		unit = "";
	}

	return to_string(num) + unit;
}