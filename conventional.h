#pragma once
#include "simulator.h"
#include "netlist_base.h"
#include "stl_config.h"
#include "single_score.h"
#include "wave_list_base.h"
#include "lis_file.h"
#include "transient_wave.h"
#include "point_score.h"
#include "evaluate_functions.h"
#include "file_utils.h"
#include "eye_log.h"
#include <memory>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

class conventional
{
public:
	conventional(string file_name, stl_config config, shared_ptr<single_score> score = make_shared<single_score>());
	~conventional();
	static void set_simulator(shared_ptr<simulator> simulator);
	static void set_template(shared_ptr<netlist_base> netlist);
	bool simulate();
	void set_waves();
	void set_scores(shared_ptr<single_score> score_conventional = NULL);
	shared_ptr<single_score> get_score_object();
	void file_copy_to(string file_path);
	void out_eye_diagram();
	shared_ptr<single_score> score_;
	string name_;
protected:
	static shared_ptr<simulator> simulator_;
	static shared_ptr<netlist_base> template_;
	stl_config config_;
	string file_path_;
	shared_ptr<netlist_base> netlist_;
	void set_translate_waves();
	void set_ac_waves();
	shared_ptr<tran_command> get_translate_time();
	shared_ptr<wave_list_base> get_wave_list();
	shared_ptr<wave_list_base> wave_list_;
	vector<shared_ptr<point_score>> evaluate_waves();
	shared_ptr<point_score> evaluate_point_score(string point, double weight, string method,
		shared_ptr<transient_wave> wave_ideal, shared_ptr<transient_wave> wave_opt);
};
