#pragma once
#include "stl_ga_log.h"
#include <string>

using namespace std;

class population_log : public stl_ga_log
{
public:
	population_log();
	~population_log();
	void static init(string file_name);
};

