#pragma once
#include "stl_ga_log.h"
#include <string>

using namespace std;

class family_log : public stl_ga_log
{
public:
	family_log();
	~family_log();
	void static init(string file_name);
};

