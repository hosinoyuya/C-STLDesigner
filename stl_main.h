#pragma once
#include "stl_config.h"
#include <string>
#include <vector>

using namespace std;

class stl_main
{
public:
	stl_main(string file_name);
	~stl_main();
private:
	stl_config config;
	vector<int> seeds;
public:
	void run();
};