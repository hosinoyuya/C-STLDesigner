#include "conventional.h"

shared_ptr<simulator> conventional::simulator_;
shared_ptr<netlist_base> conventional::template_;

conventional::conventional(string file_name, stl_config config, shared_ptr<single_score> score)
{
	name_ = file_name;
	config_ = config;
	file_path_ = config.template_file_;
	netlist_ = make_shared<netlist_base>(*template_);
	netlist_->file_path_ = file_path_;
	score_ = score;
}


conventional::~conventional()
{
}


void conventional::set_simulator(shared_ptr<simulator> simulator)
{
	simulator_ = simulator;
}


void conventional::set_template(shared_ptr<netlist_base> netlist)
{
	template_ = netlist;
}


void conventional::simulate()
{
	simulator_->simulate(file_path_);
}


void conventional::set_waves()
{
	if (netlist_->commands_->tran_ != NULL) {
		set_translate_waves();
	}
	if (netlist_->commands_->ac_ != NULL) {
		set_ac_waves();
	}
}


void conventional::set_translate_waves()
{
	shared_ptr<tran_command> tran = get_translate_time();
	wave_list_ = get_wave_list();
	wave_list_->load_tran(tran, config_);
}


void conventional::set_ac_waves()
{
	// –¢ŽÀ‘•
}


shared_ptr<tran_command> conventional::get_translate_time()
{
	if (simulator_->name_ == "hspice") {
		return template_->commands_->tran_;
	}
	else {
		cerr << "simulator = " << simulator_->name_ << " not implemented." << endl;
		exit(0);
	}
	return NULL;
}


shared_ptr<wave_list_base> conventional::get_wave_list()
{
	string wave_list_path = boost::algorithm::replace_all_copy(file_path_, config_.netlist_extension_, config_.wave_extension_);
	if (simulator_->name_ == "hspice") {
		return make_shared<lis_file>(wave_list_path);
	}
	else {
		cerr << "simulator = " << simulator_->name_ << " not implemented." << endl;
		exit(0);
	}
	return NULL;
}


void conventional::set_scores(shared_ptr<single_score> score_conventional)
{
	vector<shared_ptr<point_score>> point_scores = evaluate_waves();
	score_->set(point_scores);

	if (score_conventional && config_.score_normalize_) {
		score_->calc_ratio(score_conventional);
	}
}


vector<shared_ptr<point_score>> conventional::evaluate_waves()
{
	vector<shared_ptr<point_score>> point_scores;
	map<string, string> methods = config_.score_calc_methods_;
	for (map<string, string>::iterator itr = methods.begin(); itr != methods.end(); ++itr) {
		string point = itr->first;
		string method = itr->second;
		shared_ptr<transient_wave> wave_opt = wave_list_->waves_[point];
		shared_ptr<transient_wave> wave_ideal = wave_list_->waves_[config_.ideal_point_[point]];
		double weight = config_.score_weight_[point];
		shared_ptr<point_score> score;

		if (method == "multi") {
			// –¢ŽÀ‘•
		} 
		else if (method == "eye") {
			// –¢ŽÀ‘•
		}
		else {
			score = evaluate_point_score(point, weight, method, wave_ideal, wave_opt);
		}
		point_scores.push_back(score);
	}
	return point_scores;
}


shared_ptr<point_score>  conventional::evaluate_point_score(string point, double weight, string method,
	shared_ptr<transient_wave> wave_ideal, shared_ptr<transient_wave> wave_opt)
{
	double score;
	if (wave_ideal->size() != wave_opt->size()) {
		cerr << "Wave Size not equal.  wave_ideal = " << wave_ideal->size()
			<< ", wave_opt = " << wave_opt->size() << endl;
	}

	if (method == "integral") {
		score = evaluate_functions::calc_integral(wave_ideal->time_interval_, wave_ideal->voltage_, wave_opt->voltage_);
	}
	else {
		cerr << "Evaluate error. undefined method = " << method << endl;
	}

	shared_ptr<point_score> p_score = make_shared<point_score>(point, method);
	p_score->set(score, weight);

	return p_score;
}


shared_ptr<single_score> conventional::get_score_object()
{
	return score_;
}


void conventional::file_copy_to(string file_path)
{
	string from;
	for (size_t i = 0; i < config_.spice_extensions_.size(); i++) {
		string from_ext = config_.netlist_extension_;
		string to_ext = config_.spice_extensions_[i];
		from = file_path_;
		from.replace(from.find(from_ext), from_ext.size(), to_ext);
		file_utils::cp(from, file_path);
	}
}
