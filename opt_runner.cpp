#include "opt_runner.h"



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
	srand(seed_);
	stl_initialize();
	algorithm_->run();
}


void opt_runner::stl_initialize()
{
	set_simulator();
	set_template();


}


void opt_runner::set_simulator()
{
	string spice = config_.spice_name_;
	if (spice == "hspice") {
		std::shared_ptr<hspice> simulator(new hspice());
		conventional::set_simulator(simulator);
	} else {
		cerr << "simulator <" << spice << "> not implemented." << endl;
		exit(0);
	}
}


void opt_runner::set_template()
{
	string spice = config_.spice_name_;
	std::shared_ptr<netlist_base> template_conv = netlist_generate(spice, config_.netlist_extension_, config_.spice_extensions_, config_.spice_extensions_nouse_);
	template_conv->load(config_.template_file_);

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
