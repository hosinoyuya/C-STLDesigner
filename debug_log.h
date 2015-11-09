#pragma once
#include <string>
#include <fstream>

using namespace std;

class debug_log
{
public:
	debug_log();
	~debug_log();
	static void init(string file_name, bool debug_flag);
private:
	static string log_file_name;
	static bool debug_flag;
};

