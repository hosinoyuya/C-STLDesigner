#include "eye_log.h"


string eye_log::log_file_name_;

eye_log::eye_log()
{
}


eye_log::~eye_log()
{
}


void eye_log::init(string file_name)
{
	log_file_name_ = file_name;
}

void eye_log::write_eye_diagram(vector<vector<double>> eye_diagram)
{
	ofstream ofs(log_file_name_, ios::app);
	for (int i = 0; i < eye_diagram[0].size(); i++) {
		for (int j = 0; j < 3; j++) {
			ofs << eye_diagram[j][i] << ",";
		}
		ofs << eye_diagram[3][i] << endl;
	}
	ofs.close();
}