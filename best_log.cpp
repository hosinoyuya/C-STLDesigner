#include "best_log.h"



best_log::best_log()
{
}


best_log::~best_log()
{
}

void best_log::init(string file_name)
{
	stl_ga_log::log_file_name = file_name;
	stl_ga_log::init(file_name);
}