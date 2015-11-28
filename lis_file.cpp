#include "lis_file.h"

const regex REG_ERROR(R"(.*error.*)");
const regex REG_ANALYSIS(R"(.*analysis.*)");
const regex REG_NO_FEATURE(R"(.*No such feature exists.*)");
const regex REG_INTORO_FLAG(R"(.*transient analysis.*)");


lis_file::lis_file(string file_path) : wave_list_base(file_path)
{
}


lis_file::~lis_file()
{
}


void lis_file::load_tran(shared_ptr<tran_command> tran, stl_config config)
{
	vector<string> lis_data;
	string line;
	ifstream ifs(file_path_);
	while (getline(ifs, line)) {
		lis_data.push_back(line);
	}

	is_error(lis_data);

	int data_num = get_data_num(tran);
	remove_intoro(lis_data);

	map<string, vector<string>> data_map;
	vector<string> labels;

	while (lis_data[0] == "x") {
		map<string, vector<string>> data_map_loop;
		vector<string> labels_loop;

		data_map_loop["time"] = vector<string>(data_num);
		labels_loop.push_back("time");

		set_data_map(lis_data, data_num, data_map_loop, labels_loop);

		data_map.insert(data_map_loop.begin(), data_map_loop.end());
		labels.insert(labels.end(), labels_loop.begin(), labels_loop.end());

		if (lis_data[0] != "y") {
			cerr << "lisfile data load fail." << endl;
			exit(0);
		}
	}

	// time‚ðíœ
	labels.erase(labels.begin());
	if (wave_point_check(labels, config) == false) {
		cerr << "Wave List File is not correct (node point mismatch with config)" << endl;
	}

	for (size_t i = 0; i < labels.size(); i++) {
		shared_ptr<node_point> point = make_shared<node_point>("", labels[i]);
		shared_ptr<transient_wave> wave = make_shared<transient_wave>(point);
		wave->time_division = data_map["time"];
		wave->time_division = data_map[labels[i]];
		waves_[labels[i]] = wave;
	}

}


bool lis_file::is_error(vector<string> &lis_data)
{
	for (size_t i = 0; i < lis_data.size(); i++) {
		if (regex_match(lis_data[i], REG_ERROR) && !regex_match(lis_data[i], REG_ANALYSIS)) {
			cerr << "Lis file has error. filepath = " << file_path_ << endl;
			return true;
		}
		if (regex_match(lis_data[i], REG_NO_FEATURE)) {
			cerr << "spice license error. filepath = " << file_path_ << endl;
			return true;
		}
	}
	return false;
}


int lis_file::get_data_num(shared_ptr<tran_command> tran)
{
	double resolution = stod(tran->resolution_);
	double start_time = stod(tran->start_time_);
	double end_time = stod(tran->end_time_);

	return (int)(fabs(end_time - start_time) / resolution + 1);
}


void lis_file::remove_intoro(vector<string> &lis_data)
{
	while (lis_data.size() > 0 && !regex_match(lis_data[0], REG_INTORO_FLAG)) {
		lis_data.erase(lis_data.begin());
	}
	lis_data.erase(lis_data.begin());
}


void lis_file::set_data_map(vector<string> &lis_data, int data_num, map<string, vector<string>> &data_map_loop, vector<string> &labels_loop)
{
	vector<string> items;

	for (int i = 0; i < 3; i++) {
		lis_data.erase(lis_data.begin());
	}

	boost::algorithm::split(items, lis_data[0], boost::algorithm::is_space(), boost::algorithm::token_compress_on);
	for (size_t i = 0; i < items.size(); i++) {
		if (items[i] == "") continue;
		labels_loop.push_back(items[i]);
		data_map_loop[items[i]] = vector<string>(data_num);
	}

	lis_data.erase(lis_data.begin());

	for (int i = 0; i < data_num; i++) {
		boost::algorithm::split(items, lis_data[0], boost::algorithm::is_space(), boost::algorithm::token_compress_on);
		for (size_t j = 0; j < labels_loop.size(); j++) {
			data_map_loop[labels_loop[j]][i] = items[j];
		}
		lis_data.erase(lis_data.begin());
	}
}


bool lis_file::wave_point_check(vector<string> labels, stl_config config)
{
	map<string, string> method = config.score_calc_methods_;
	for (size_t i = 0; i < labels.size(); i++) {
		if (method.find(labels[i]) != method.end()) {
			method.erase(labels[i]);
		}
	}
	if (method.size() == 0) {
		return true;
	}
	false;
}