#include "opt_runner.h"

shared_ptr<single_score> stl::comparison_score_;

opt_runner::opt_runner(stl_config config, int seed)
{
	opt_runner::config_ = config;
	opt_runner::seed_ = seed;
	
	if (config.optimization_ == "ga") {
		algorithm_ = make_shared<ga_opt>(config, seed);
	}
	else {
		cerr << "undefined optimization type: " << config.optimization_ << "," << endl;
		cerr << "please correct the algorithm setting in your config file." << endl;
		exit(0);
	}
}


opt_runner::~opt_runner()
{
}


void opt_runner::run()
{
	stl_random::srand(seed_);
	stl_initialize();
	algorithm_->run();
}


void opt_runner::stl_initialize()
{
	set_simulator();
	set_template();

	conventional_ = get_conventional();
	
	conventional_->simulate();
	conventional_->set_waves();
	set_conventional_score(conventional_);
	conventional_->file_copy_to(config_.population_directory_ + "/..");
}


void opt_runner::set_simulator()
{
	string spice = config_.spice_name_;
	if (spice == "hspice") {
		shared_ptr<hspice> simulator_conv(new hspice(config_));
		conventional::set_simulator(simulator_conv);
		shared_ptr<hspice> simulator_stl(new hspice(config_));
		stl::set_simulator(simulator_stl);
	} else {
		cerr << "simulator <" << spice << "> not implemented." << endl;
		exit(0);
	}
}


void opt_runner::set_template()
{
	string spice = config_.spice_name_;
	shared_ptr<netlist_base> template_conv = netlist_generate(spice, config_.netlist_extension_, config_.spice_extensions_, config_.spice_extensions_nouse_);
	template_conv->load(config_.template_file_);
	conventional::set_template(template_conv);

	shared_ptr<netlist_base> template_stl = netlist_generate(spice, config_.netlist_extension_, config_.spice_extensions_, config_.spice_extensions_nouse_);
	template_stl->load(config_.template_file_);
	stl::set_template(template_stl);
}


shared_ptr<netlist_base> opt_runner::netlist_generate(string spice, string extention, vector<string> spice_extentions, vector<string> spice_extensions_nouse)
{
	if (spice == "hspice") {
		if (extention == "") {
			extention = ".sp";
		}
		return make_shared<hspice_netlist>(extention, spice_extentions, spice_extensions_nouse);
	}
	else {
		cerr << "simulator <" << spice << "> not implemented." << endl;
		exit(0);
	}
	shared_ptr<netlist_base> template_conv;
	return template_conv;
}


shared_ptr<conventional> opt_runner::get_conventional()
{
	boost::filesystem::path path(config_.template_file_);
	return make_shared<conventional>(path.filename().string(), config_, make_shared<single_score>());
}


void opt_runner::set_conventional_score(shared_ptr<conventional> conventional)
{
	conventional->set_scores();
	stl::comparison_score_ = conventional->get_score_object();
}