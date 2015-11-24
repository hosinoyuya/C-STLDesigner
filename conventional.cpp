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

	// TODO �g�`���擾�ł��Ă��Ȃ��Ƃ��̏���
	
}


void conventional::set_translate_waves()
{

}


void conventional::set_emit_waves()
{

}


void conventional::set_ac_waves()
{

}