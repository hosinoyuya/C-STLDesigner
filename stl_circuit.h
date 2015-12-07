#pragma once
#include "netlist_circuit.h"
#include "sub_space.h"
#include "element.h"
#include <vector>
#include <list>
#include <memory>

using namespace std;

class stl_circuit :
	public netlist_circuit
{
public:
	stl_circuit(string header = "");
	~stl_circuit();
	void exchange_subspace(shared_ptr<sub_space> &subspace);
	virtual string to_str();
private:
	void exchange_element(list<shared_ptr<element>>::iterator &element_itr, list<string>::iterator &comment_itr,
		shared_ptr<sub_space> &subspace);
};