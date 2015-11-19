#include "debug_log.h"


string debug_log::log_file_name_;
bool debug_log::debug_flag_;

debug_log::debug_log()
{
}


debug_log::~debug_log()
{
}


void debug_log::init(string file_name, bool debug_flag)
{
	debug_log::log_file_name_ = file_name;
	debug_log::debug_flag_ = debug_flag;
	ofstream ofs(file_name);
	ofs << "# STL Designer 2 generic logfile" << endl;
	ofs.close();
}