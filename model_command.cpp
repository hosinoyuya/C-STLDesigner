#include "model_command.h"

const regex REG_R(R"(.*r.*)", regex_constants::icase);
const regex REG_L(R"(.*l.*)", regex_constants::icase);
const regex REG_G(R"(.*g.*)", regex_constants::icase);
const regex REG_C(R"(.*c.*)", regex_constants::icase);


model_command::model_command()
{
}


model_command::~model_command()
{
}


void model_command::set_parameters(string line)
{
	string copy_line = boost::algorithm::replace_all_copy(line, "+", " ");
	vector<string> items, sub_items;
	boost::algorithm::split(items, copy_line, boost::algorithm::is_space(), boost::algorithm::token_compress_on);
	key_ = items[0];
	items.erase(items.begin());
	name_ = items[0];
	items.erase(items.begin());
	element_ = items[0];
	items.erase(items.begin());
	boost::algorithm::split(sub_items, items[0], boost::is_any_of("="), boost::algorithm::token_compress_on);
	type_ = sub_items[1];
	items.erase(items.begin());
	boost::algorithm::split(sub_items, items[0], boost::is_any_of("="), boost::algorithm::token_compress_on);
	string net_num = sub_items[1];
	net_num_ = stoi(net_num);
	items.erase(items.begin());

	set_rlgc(items);
}


string model_command::to_str()
{
	return "";
}


void model_command::set_rlgc(vector<string> items) {
	for (size_t i = 0; i < items.size(); i++) {
		if (regex_match(items[i], REG_R)) {
			r_ = make_shared<rlgc_model>(boost::algorithm::replace_all_copy(items[i], "=", ""), net_num_);
			rlgc_models_.push_back(r_);
			continue;
		}
		if (regex_match(items[i], REG_L)) {
			l_ = make_shared<rlgc_model>(boost::algorithm::replace_all_copy(items[i], "=", ""), net_num_);
			rlgc_models_.push_back(l_);
			continue;
		}
		if (regex_match(items[i], REG_G)) {
			g_ = make_shared<rlgc_model>(boost::algorithm::replace_all_copy(items[i], "=", ""), net_num_);
			rlgc_models_.push_back(g_);
			continue;
		}
		if (regex_match(items[i], REG_C)) {
			c_ = make_shared<rlgc_model>(boost::algorithm::replace_all_copy(items[i], "=", ""), net_num_);
			rlgc_models_.push_back(c_);
			continue;
		}
		rlgc_models_[rlgc_models_.size() - 1]->set_value(items[i]);
	}
}