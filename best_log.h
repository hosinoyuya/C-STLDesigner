#pragma once
#include "stl_ga_log.h"
#include <string>

using namespace std;

class best_log : public stl_ga_log
{
public:
	best_log();
	~best_log();
	void static init(string file_name);
};

