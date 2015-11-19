#include "unit_change.h"

const regex NUM(R"(\d+)");

const regex CENTI(R"(c)");
const regex MILLI(R"(m)");
const regex MICRO(R"(u)");
const regex NANO(R"(n)");
const regex PICO(R"(p)");
const regex FEMTO(R"(f)");
const regex ATTO(R"(a)");
const regex ZEPTO(R"(z)");
const regex YOCTO(R"(y)");

unit_change::unit_change()
{
}


unit_change::~unit_change()
{
}


string unit_change::unit_decode(string str)
{
	if (regex_match(str, NUM) || str == "") {
		return str;
	}

	smatch m;
	regex_search(str, m, CENTI);
	if (m.size() > 0) {
		return regex_replace(str, CENTI, "e-2");
	}
	regex_search(str, m, MILLI);
	if (m.size() > 0) {
		return regex_replace(str, MILLI, "e-3");
	}
	regex_search(str, m, MICRO);
	if (m.size() > 0) {
		return regex_replace(str, MICRO, "e-6");
	}
	regex_search(str, m, NANO);
	if (m.size() > 0) {
		return regex_replace(str, NANO, "e-9");
	}
	regex_search(str, m, PICO);
	if (m.size() > 0) {
		return regex_replace(str, PICO, "e-12");
	}
	regex_search(str, m, FEMTO);
	if (m.size() > 0) {
		return regex_replace(str, FEMTO, "e-15");
	}
	regex_search(str, m, ATTO);
	if (m.size() > 0) {
		// regex_replace(str, ATTO, "e-18");
		return "0.0";
	}
	regex_search(str, m, ZEPTO);
	if (m.size() > 0) {
		// regex_replace(str, ZEPTO, "e-21");
		return "0.0";
	}
	regex_search(str, m, YOCTO);
	if (m.size() > 0) {
		// regex_replace(str, ATTO, "e-24");
		return "0.0";
	}

	return str;
}