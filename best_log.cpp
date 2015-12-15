#include "best_log.h"

string best_log::log_file_name_;

best_log::best_log()
{
}


best_log::~best_log()
{
}


void best_log::init(string file_name)
{
	log_file_name_ = file_name;
	stl_ga_log::init(file_name);
}


void best_log::puts_stl(int generation, vector<shared_ptr<stl>> stls)
{
	stl_ga_log::puts_stl(generation, stls, log_file_name_);
}