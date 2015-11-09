#include "population_log.h"



population_log::population_log()
{
}


population_log::~population_log()
{
}


void population_log::init(string file_name)
{
	stl_ga_log::log_file_name = file_name;
	stl_ga_log::init(file_name);
}
