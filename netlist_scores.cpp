#include "netlist_scores.h"



netlist_scores::netlist_scores()
{
	header_ = "*** Scores *** -------------------------------------------------------------*\n";
}


netlist_scores::~netlist_scores()
{
}


string netlist_scores::to_str()
{
	string return_string = header_ + "\n";

	for (size_t i = 0; i < context_.size(); i++) {
		return_string += context_[i] + "\n";
	}

	return_string += "\n";

	return return_string;
}


void netlist_scores::set_single_score(shared_ptr<single_score> score)
{
	context_.push_back(score->to_str());
}