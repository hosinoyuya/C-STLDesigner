#pragma once
#include "netlist_context.h"
#include "single_score.h"
#include <string>

using namespace std;

class netlist_scores :
	public netlist_context
{
public:
	netlist_scores();
	~netlist_scores();
	virtual string to_str();
	void set_single_score(shared_ptr<single_score> score);
};

