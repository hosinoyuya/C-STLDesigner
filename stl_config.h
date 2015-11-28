#pragma once
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

using namespace std;

class stl_config
{
public:
	stl_config();
	~stl_config();
	void load(string file_path);
private:
	void setDefault();
	void setParameters(YAML::Node config);
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
	double minimum_inpedance_;
	double maximum_inpedance_;
	double impedance_step_;
	map<double, string> impedance_type_;
	string minimum_length_;
	string length_step_;
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
	void chane_outdirectory_seed(int seed);
};
