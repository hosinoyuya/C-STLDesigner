#include "rlgc_model.h"



rlgc_model::rlgc_model(string key, int net_num)
{
	key_ = key;
	net_num_ = net_num;
}


rlgc_model::~rlgc_model()
{
}


void rlgc_model::set_value(string val) {
	values_.push_back(val);
}
