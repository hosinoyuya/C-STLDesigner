#include "stl_circuit.h"



stl_circuit::stl_circuit(string header) : netlist_circuit(header)
{
}


stl_circuit::~stl_circuit()
{
}


void stl_circuit::exchange_subspace(shared_ptr<sub_space> &subspace)
{
	int element_count = 0;
	list<string>::iterator comment_itr = comments_.begin();
	list<shared_ptr<element>>::iterator element_itr = elements_.begin();
	while (comment_itr != comments_.end() && element_itr != elements_.end()) {
		if (*comment_itr == "") {
			if ((*element_itr) && (*element_itr)->name_ == subspace->name_) {
				exchange_element(element_itr, comment_itr, subspace);
				element_itr--; // QÆ‚µ‚Ä‚¢‚½element‚ªíœ‚³‚êiterator‚ª‚¸‚ê‚é‚½‚ß
				comment_itr--;
			}
			element_itr++;
		}
		comment_itr++;
	}
}

void stl_circuit::exchange_element(list<shared_ptr<element>>::iterator &element_itr, list<string>::iterator &comment_itr,
	shared_ptr<sub_space> &subspace)
{
	vector<shared_ptr<element>> segments = subspace->segments_;
	for (size_t i = 0; i < segments.size(); i++) {
		elements_.insert(element_itr, segments[i]);
		comments_.insert(comment_itr, "");
	}
	element_itr = elements_.erase(element_itr);
	comment_itr = comments_.erase(comment_itr);
}