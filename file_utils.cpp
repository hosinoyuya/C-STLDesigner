#include "file_utils.h"



file_utils::file_utils()
{
}


file_utils::~file_utils()
{
}


bool file_utils::rm_r(string path)
{
	cout << path << endl;
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
					cout << "removed:" << fullpath << endl;
				}
			}
			boost::filesystem::remove(path);
			cout << "removed:" << path << endl;
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
	boost::filesystem::create_directories(directory);
	return true;
}
