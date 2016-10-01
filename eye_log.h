#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class eye_log
{
public:
	eye_log();
	~eye_log();
	void static init(string file_name);
	void static write_eye_diagram(vector<vector<double>> eye_diagram);
protected:
	static string log_file_name_;
};

