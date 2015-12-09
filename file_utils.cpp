#include "file_utils.h"



file_utils::file_utils()
{
}


file_utils::~file_utils()
{
}


bool file_utils::rm_r(string path)
{
	boost::filesystem::path directory(path);
	boost::filesystem::directory_iterator end;
	if (boost::filesystem::exists(directory)) {
		try {
			for (boost::filesystem::directory_iterator itr(directory); itr != end; ++itr) {
				string fullpath = itr->path().string();
				if (boost::filesystem::is_directory(*itr)) {
					if (!rm_r(fullpath)) {
						return false;
					}
				}
				else {
					boost::filesystem::remove(fullpath);
				}
			}
			boost::filesystem::remove(path);
		}
		catch (const boost::filesystem::filesystem_error& e) {
			cerr << e.what() << endl;
			return false;
		}
	}
	return true;
}


bool file_utils::mkdir(string directory)
{
	return boost::filesystem::create_directories(directory);
}


bool file_utils::cp(string from_file, string to_directory)
{
	boost::filesystem::path from(from_file);
	string file_name = from.filename().string();
	try {
		boost::filesystem::copy_file(from, to_directory + "/" + file_name, boost::filesystem::copy_option::overwrite_if_exists);
	}
	catch (const boost::filesystem::filesystem_error& e) {
		cerr << e.what() << endl;
		return false;
	}
	return true;
}