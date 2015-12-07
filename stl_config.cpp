#include "stl_config.h"

stl_config::stl_config()
{
	set_default();
}


stl_config::~stl_config()
{
}


void stl_config::set_default()
{
	out_directory_ = "./output";
	log_directory_ = out_directory_ + "/stl/log";
	population_directory_ = out_directory_ + "/stl/population";
	best_directory_ = out_directory_ + "/stl/best";
	image_directory_ = out_directory_ + "/stl/images";
	template_file_ = "./template/default.sp";
	population_size_ = 2;
	generation_num_ = 2;
	brother_num_ = 2;
	blx_alpha_ = 0.366;
	crossover_["length"] = "dependent_sum_blx";
	crossover_["impedance"] = "independent_blx";
	minimum_inpedance_ = 40;
	maximum_inpedance_ = 120;
	impedance_step_ = 5;
	minimum_length_ = 0.001;
	length_step_ = 0.0005;
	impedance_type_[40] = 6407e-12;
	impedance_type_[45] = 6355e-12;
	impedance_type_[50] = 6308e-12;
	impedance_type_[55] = 6266e-12;
	impedance_type_[60] = 6226e-12;
	impedance_type_[65] = 6188e-12;
	impedance_type_[70] = 6156e-12;
	impedance_type_[75] = 6125e-12;
	impedance_type_[80] = 6099e-12;
	impedance_type_[85] = 6075e-12;
	impedance_type_[90] = 6055e-12;
	impedance_type_[95] = 6034e-12;
	impedance_type_[100] = 6015e-12;
	impedance_type_[105] = 5999e-12;
	impedance_type_[110] = 5980e-12;
	impedance_type_[115] = 5965e-12;
	impedance_type_[120] = 5954e-12;
	seeds_ = { 1, 2 };
	optimization_ = "ga";
	spice_name_ = "hspice";
	optimize_point_ = { "optpt1", "optpt2" };
	score_weight_["optpt1"] = 1.0;
	score_weight_["optpt2"] = 1.0;
	ideal_point_["optpt1"] = "vspt1";
	ideal_point_["optpt2"] = "vspt2";
	line_offset_ = 100;
	sub_offset_ = 1000;
	debug_log_ = true;
	lotation_step_ = 10;
	netlist_extension_ = ".sp";
	wave_extension_ = ".lis";
	spice_extensions_ = { ".sp", ".lis", ".st0", /*".tr0",*/ ".ic0" };
	spice_extensions_nouse_ = { ".st0", ".tr0", ".ic0" };
	score_normalize_ = true;
	score_calc_methods_["optpt1"] = "integral";
	score_calc_methods_["optpt2"] = "integral";
}


void stl_config::load(string file_path)
{
	size_t pos = file_path.rfind('/');
	if (pos != string::npos) {
		file_name_ = file_path.substr(pos + 1, file_path.size() - pos - 1);
	}
	else {
		file_name_ = file_path;
	}

	file_path_ = file_path;
	YAML::Node config = YAML::LoadFile(file_path);
	set_parameters(config);

	config_control();
}


void stl_config::set_parameters(YAML::Node config) {
	for (YAML::const_iterator it = config.begin(); it != config.end(); it++) {
		string key = it->first.as<string>();
		if (key == "outdir") {
			out_directory_ = it->second.as<string>();
		}
		else if (key == "logdir") {
			log_directory_ = it->second.as<string>();
		}
		else if (key == "popdir") {
			population_directory_ = it->second.as<string>();
		}
		else if (key == "bestdir") {
			best_directory_ = it->second.as<string>();
		}
		else if (key == "imgdir") {
			image_directory_ = it->second.as<string>();
		}
		else if (key == "template") {
			template_file_ = it->second.as<string>();
		}
		else if (key == "pop_size") {
			population_size_ = it->second.as<int>();
		}
		else if (key == "generation") {
			generation_num_ = it->second.as<int>();
		}
		else if (key == "brother_num") {
			brother_num_ = it->second.as<int>();
		}
		else if (key == "blx_alpha") {
			blx_alpha_ = unit_change::unit_decode(it->second.as<string>());
		}
		else if (key == "crossover") {
			crossover_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				crossover_.insert(pair<string, string>(it2->first.as<string>(), it2->second.as<string>()));
			}
		}
		else if (key == "minimum_impedance") {
			minimum_inpedance_ = it->second.as<int>();
		}
		else if (key == "maximum_impedance") {
			maximum_inpedance_ = it->second.as<int>();
		}
		else if (key == "impedance_step") {
		}
		else if (key == "minimum_length") {
			minimum_length_ = unit_change::unit_decode(it->second.as<string>());
		}
		else if (key == "length_step") {
			length_step_ = unit_change::unit_decode(it->second.as<string>());
		}
		else if (key == "imptype") {
			impedance_type_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				impedance_type_.insert(pair<int, double>(it2->first.as<int>(), it2->second.as<double>()));
			}
		}
		else if (key == "seeds") {
			seeds_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				seeds_.push_back(it2->as<int>());
			}
		}
		else if (key == "optimization") {
			optimization_ = it->second.as<string>();
		}
		else if (key == "spice_name") {
			spice_name_ = it->second.as<string>();
		}
		else if (key == "optpts") {
			optimize_point_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				optimize_point_.push_back(it2->as<string>());
			}
		}
		else if (key == "weight") {
			score_weight_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				score_weight_.insert(pair<string, double>(it2->first.as<string>(), it2->second.as<double>()));
			}
		}
		else if (key == "versus") {
			ideal_point_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				ideal_point_.insert(pair<string, string>(it2->first.as<string>(), it2->second.as<string>()));
			}
		}
		else if (key == "line_offset") {
			line_offset_ = it->second.as<int>();
		}
		else if (key == "sub_offset") {
			sub_offset_ = it->second.as<int>();
		}
		else if (key == "debuglog") {
			string bool_string = it->second.as<string>();
			if (bool_string == "true") {
				debug_log_ = true;
			}
			else {
				debug_log_ = false;
			}
		}
		else if (key == "line_offset") {
			line_offset_ = it->second.as<int>();
		}
		else if (key == "lotation_step") {
			lotation_step_ = it->second.as<int>();
		}
		else if (key == "netlist_ext") {
			netlist_extension_ = it->second.as<string>();
		}
		else if (key == "wave_ext") {
			wave_extension_ = it->second.as<string>();
		}
		else if (key == "spice_exts") {
			spice_extensions_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				spice_extensions_.push_back(it2->as<string>());
			}
		}
		else if (key == "spice_exts_nouse") {
			spice_extensions_nouse_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				spice_extensions_nouse_.push_back(it2->as<string>());
			}
		}
		else if (key == "score_normalize") {
			string bool_string = it->second.as<string>();
			if (bool_string == "true") {
				score_normalize_ = true;
			}
			else {
				score_normalize_ = false;
			}
		}
		else if (key == "score_calc_methods") {
			score_calc_methods_.clear();
			for (YAML::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				score_calc_methods_.insert(pair<string, string>(it2->begin()->as<string>(), (++(it2->begin()))->as<string>()));
			}
		}
	}
}



void stl_config::chane_outdirectory_seed(int seed)
{
	ostringstream oss;
	oss << "seed_" << seed;
	string seed_string = oss.str();
	string find_string;
	find_string = "/log";
	log_directory_.replace(log_directory_.find(find_string),
		find_string.size(), "/" + seed_string + find_string);
	find_string = "/population";
	population_directory_.replace(population_directory_.find(find_string),
		find_string.size(), "/" + seed_string + find_string);
	find_string = "/best";
	best_directory_.replace(best_directory_.find(find_string),
		find_string.size(), "/" + seed_string + find_string);
	find_string = "/images";
	image_directory_.replace(image_directory_.find(find_string),
		find_string.size(), "/" + seed_string + find_string);
}


void stl_config::config_control()
{
	boost::filesystem::path file_path(file_path_);
	string directory_name = file_path.parent_path().string();
	string file_name = file_path.filename().string();
	boost::algorithm::replace_all(directory_name, "./", "");
	boost::algorithm::replace_all(directory_name, "config/", "");
	boost::algorithm::replace_all(directory_name, "/", "_");
	boost::algorithm::replace_all(directory_name, "__", "_");
	vector<string> items;
	boost::algorithm::split(items, file_name, boost::algorithm::is_any_of("."), boost::algorithm::token_compress_on);
	file_name = items[0];
	boost::algorithm::replace_all(file_name, "config_", "");
	string out_name = "STL_" + directory_name + "_" + file_name;

	log_directory_ = out_directory_ + "/" + out_name + "/log";
	population_directory_ = out_directory_ + "/" + out_name + "/population";
	best_directory_ = out_directory_ + "/" + out_name + "/best";
	image_directory_ = out_directory_ + "/" + out_name + "/images";
}