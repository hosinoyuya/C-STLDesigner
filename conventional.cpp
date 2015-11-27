#include "conventional.h"

shared_ptr<simulator> conventional::simulator_;
shared_ptr<netlist_base> conventional::template_;

conventional::conventional(stl_config config, shared_ptr<single_score> score)
{
	boost::filesystem::path path(config_.template_file_);
	string filename_ = path.filename().string();
	config_ = config;
	file_path_ = config.template_file_;
	netlist_ = make_shared<netlist_base>(*template_);
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
	set_emit_waves();
	if (netlist_->commands_->ac_ != NULL) {
		set_ac_waves();
	}

	// TODO ”gŒ`‚ğæ“¾‚Å‚«‚Ä‚¢‚È‚¢‚Æ‚«‚Ìˆ—
	
}


void conventional::set_translate_waves()
{
	shared_ptr<tran_command> tran = get_translate_time();
	wave_list_ = get_wave_list();
	wave_list_->load_tran(tran);

	// now writing
}


void conventional::set_emit_waves()
{

}


void conventional::set_ac_waves()
{

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