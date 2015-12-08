#pragma once
#include "netlist_circuit.h"
#include "sub_space.h"
#include "element.h"
#include <vector>
#include <list>
#include <memory>
#include <algorithm>

using namespace std;

class stl_circuit :
	public netlist_circuit
{
public:
	stl_circuit(string header = "");
	~stl_circuit();
	void exchange_subspace(shared_ptr<sub_space> &subspace);
	virtual string to_str();
	void copy_stl_circuit_contents();
private:
	void exchange_element(list<shared_ptr<element>>::iterator &element_itr, list<string>::iterator &comment_itr,
		shared_ptr<sub_space> &subspace);
	list<string> exchanged_comments_;
	list<shared_ptr<element>> exchanged_elements_;
};