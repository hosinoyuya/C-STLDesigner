#include "population_log.h"

int population_log::log_num_ = 1;
string population_log::log_file_name_;

population_log::population_log()
{
}


population_log::~population_log()
{
}

void population_log::init(string file_name)
{
	log_file_name_ = file_name;
	stl_ga_log::init(file_name);
}


void population_log::puts_stl(int generation, vector<shared_ptr<stl>> stls)
{
	stl_ga_log::puts_stl(generation, stls, log_file_name_);
}

void population_log::lotation(int generation, int lotation_step)
{
	if (generation % lotation_step != 0) {
		return;
	}

	boost::filesystem::path path(log_file_name_);
	string ext = path.extension().string();
	std::regex reg_ext("-[0-9]*" + ext);
	string origin = regex_replace(log_file_name_, reg_ext, ext);
	string new_file_name = boost::algorithm::replace_all_copy(origin, ext, "-" + to_string(log_num_) + ext);
	init(new_file_name);
	log_num_++;
}
