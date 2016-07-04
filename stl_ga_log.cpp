#include "stl_ga_log.h"

string stl_ga_log::log_file_name_;

stl_ga_log::stl_ga_log()
{
}


stl_ga_log::~stl_ga_log()
{
}


void stl_ga_log::init(string file_name)
{
	ofstream ofs(file_name);
	ofs << "#generation, index, filename, score, shift" << endl;
	ofs.close();
}


void stl_ga_log::puts_stl(int generation, vector<shared_ptr<stl>> stls, string file_name)
{
	ofstream ofs(file_name, ios::app);
	for (size_t i = 0; i < stls.size(); i++) {
		ofs << generation << "," << stls[i]->index_ << "," << stls[i]->name_ << "," << stls[i]->score_->value_ <<
			"," << stls[i]->score_->max_shift_ << endl;
	}
}
