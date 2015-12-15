#include "stl_circuit.h"



stl_circuit::stl_circuit(string header) : netlist_circuit(header)
{
}


stl_circuit::~stl_circuit()
{
}


void stl_circuit::exchange_subspace(shared_ptr<sub_space> &subspace)
{
	list<string>::iterator comment_itr = exchanged_comments_.begin();
	list<shared_ptr<element>>::iterator element_itr = exchanged_elements_.begin();
	while (comment_itr != exchanged_comments_.end() && element_itr != exchanged_elements_.end()) {
		if (*comment_itr == "") {
			if ((*element_itr) && (*element_itr)->name_ == subspace->name_) {
				exchange_element(element_itr, comment_itr, subspace);
				element_itr--; // 参照していたelementが削除されiteratorがずれるため
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
		exchanged_elements_.insert(element_itr, segments[i]);
		exchanged_comments_.insert(comment_itr, "");
	}
	element_itr = exchanged_elements_.erase(element_itr);
	comment_itr = exchanged_comments_.erase(comment_itr);
}


string stl_circuit::to_str()
{
	string return_string = header_ + "\n";

	list<string>::iterator comment_itr = exchanged_comments_.begin();
	list<shared_ptr<element>>::iterator element_itr = exchanged_elements_.begin();
	while (comment_itr != exchanged_comments_.end() && element_itr != exchanged_elements_.end()) {
		if (*comment_itr == "") {
			if ((*element_itr)) {
				return_string += (*element_itr)->to_str() + "\n";
			}
			else {
				return_string += "\n";
			}
			element_itr++;
		}
		else {
			return_string += *comment_itr + "\n";
		}
		comment_itr++;
	}

	return_string += "\n";

	return return_string;
}


// 書き換え用リストにコンテンツをコピー
void stl_circuit::copy_default_contents()
{
	exchanged_comments_.resize(comments_.size());
	exchanged_elements_.resize(elements_.size());

	copy(comments_.begin(), comments_.end(), exchanged_comments_.begin());
	copy(elements_.begin(), elements_.end(), exchanged_elements_.begin());
}