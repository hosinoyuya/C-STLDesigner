#pragma once
#include "netlist_context.h"
#include "element.h"
#include <list>
#include <memory>

using namespace std;

class netlist_circuit :
	public netlist_context
{
public:
	netlist_circuit(string header = "");
	~netlist_circuit();
	virtual void parce();
	list<shared_ptr<element>> elements_;
protected:
	list<string> comments_;
	
};

