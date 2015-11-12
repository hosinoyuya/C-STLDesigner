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
	stl_ga_log::log_file_name_ = file_name;
	ofstream ofs(file_name);
	ofs << "#generation, index, filename, score" << endl;
	ofs.close();
}
