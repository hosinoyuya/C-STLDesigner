#pragma once
#include "unit_change.h"
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

class stl_config
{
public:
	stl_config();
	~stl_config();
	void load(string file_path);
private:
	void set_default();
	void set_parameters(YAML::Node config);
	void config_control();
public:
	string out_directory_;
	string log_directory_;
	string population_directory_;
	string best_directory_;
	string image_directory_;
	string template_file_;
	int population_size_;
	int generation_num_;
	int brother_num_;
	double blx_alpha_;
	map<string, string> crossover_;
	int minimum_inpedance_;
	int maximum_inpedance_;
	int impedance_step_;
	map<int, double> impedance_type_;
	double minimum_capacitance_;
	double maximum_capacitance_;
	double capacitance_step_;
	vector<double> capacitance_values_;
	int cap_interval_change_;
	vector<int> capacitor_nums_;
	double minimum_length_;
	double length_step_;
	vector<double> line_lengths_;
	vector<double> sub_space_lengths_;
	vector<int> seeds_;
	// int optimizing_seed_;
	string optimization_;
	string spice_name_;
	vector<string> optimize_point_;
	map<string, double> score_weight_;
	map<string, string> ideal_point_;
	int line_offset_;
	int sub_offset_;
	bool debug_log_;
	int lotation_step_;
	string netlist_extension_;
	string wave_extension_;
	vector<string> spice_extensions_;
	vector<string> spice_extensions_nouse_;
	bool score_normalize_;
	map<string, string> score_calc_methods_;
	string file_name_;
	string file_path_;
	int server_num_;
	bool use_multithread_;
	void chane_outdirectory_seed(int seed);
	string ga_algorithm_;
	double eye_height_weight_;
	double eye_width_weight_;
	double mutation_;
	string mutation_type_;
	double shift_ratio_;
	double eye_time_;
	double eye_width_margin_;
};
