#include "family_log.h"



family_log::family_log()
{
}


family_log::~family_log()
{
}

void family_log::init(string file_name)
{
	stl_ga_log::log_file_name_ = file_name;
	stl_ga_log::init(file_name);
}