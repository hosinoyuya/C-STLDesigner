#pragma once
#include "stl_config.h"
#include "file_utils.h"
#include <string>
#include <vector>

using namespace std;
using namespace boost;

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
private:
	void directory_init(stl_config config);
};