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
protected:
	vector<shared_ptr<element>> elements_;
	vector<string> comments_;
};

