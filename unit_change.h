#pragma once
#include <string>
#include <regex>
#include <cctype>

using namespace std;

class unit_change
{
public:
	unit_change();
	~unit_change();
	static double unit_decode(string str);
};

