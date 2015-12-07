#include "rlgc_model.h"



rlgc_model::rlgc_model(string key, int net_num)
{
	key_ = key;
	net_num_ = net_num;
}


rlgc_model::~rlgc_model()
{
}


void rlgc_model::set_value(double val) {
	values_.push_back(val);
}


string rlgc_model::to_str()
{
	string return_string = key_ + "=\n";
	for (size_t i = 0; i < values_.size(); i++) {
		return_string += "+ " + unit_change::unit_encode(values_[i]) + "\n";
	}

	return return_string;
}