#pragma once
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;

class file_utils
{
public:
	file_utils();
	~file_utils();
	static bool rm(string file_name);
	static bool rm_r(string directory_name);
	static bool mkdir(string directory);
	static bool cp(string from_file, string to_directory);
};

