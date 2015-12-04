#pragma once
#include "netlist_context.h"
#include "element.h"
#include <vector>
#include <memory>

using namespace std;

class netlist_circuit :
	public netlist_context
{
public:
	netlist_circuit(string header = "");
	~netlist_circuit();
	virtual void parce();
	vector<shared_ptr<element>> elements_;
protected:
	vector<string> comments_;
};

