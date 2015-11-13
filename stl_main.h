#pragma once
#include "stl_config.h"
#include "file_utils.h"
#include "debug_log.h"
#include "population_log.h"
#include "family_log.h"
#include "best_log.h"
#include "opt_runner.h"
#include <string>
#include <vector>

using namespace std;

class stl_main
{
public:
	stl_main(string file_name);
	~stl_main();
private:
	stl_config config_;
	vector<int> seeds_;
public:
	void run();
private:
	void directory_init(stl_config config);
	void log_init(stl_config config);
	bool run_optrunner(stl_config config, int seed);
};