#pragma once
#include "simulator.h"
#include "netlist_base.h"
#include <memory>

using namespace std;

class conventional
{
public:
	conventional();
	~conventional();
	static void set_simulator(std::shared_ptr<simulator> simulator);
	static void set_template(std::shared_ptr<netlist_base> netlist);
private:
	static std::shared_ptr<simulator> simulator_;
	static std::shared_ptr<netlist_base> netlist_;
};

