#pragma once
#include "stl_ga_log.h"
#include <string>
#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <regex>

using namespace std;

class population_log : public stl_ga_log
{
public:
	population_log();
	~population_log();
	void static init(string file_name);
	void static puts_stl(int generation, vector<shared_ptr<stl>> stls);
	void static lotation(int generation, int lotation_step);
	static int log_num_;
protected:
	static string log_file_name_;
};

