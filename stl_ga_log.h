#pragma once
#include "stl.h"
#include <string>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

class stl_ga_log
{
public:
	stl_ga_log();
	~stl_ga_log();
protected:
	void static init(string file_name);
	void static puts_stl(int generation, vector<shared_ptr<stl>> stls, string file_name);
	static string log_file_name_;
};

