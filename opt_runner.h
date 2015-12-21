#pragma once
#include "stl_config.h"
#include "ga_opt.h"
#include "conventional.h"
#include "stl.h"
#include "hspice.h"
#include "netlist_base.h"
#include "hspice_netlist.h"
#include "stl_random.h"
#include "stl_signal.h"
#include <iostream>
#include <memory>
#include <boost/filesystem/path.hpp>

using namespace std;

class opt_runner
{
public:
	opt_runner(stl_config config, int seed);
	~opt_runner();
	void run();
private:
	std::shared_ptr<netlist_base> netlist_generate(string spice, string extention, vector<string> spice_extentions, vector<string> spice_extensions_nouse);
	std::shared_ptr<conventional> get_conventional();
	stl_config config_;
	int seed_;
	std::shared_ptr<ga_opt> algorithm_;
	void stl_initialize();
	void set_simulator();
	void set_template();
	std::shared_ptr<conventional> conventional_;
	void set_conventional_score(shared_ptr<conventional> conventional);
};

