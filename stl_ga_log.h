#pragma once
#include <string>
#include <fstream>

using namespace std;

class stl_ga_log
{
public:
	stl_ga_log();
	~stl_ga_log();
	void static init(string file_name);
protected:
	static string log_file_name;
};

