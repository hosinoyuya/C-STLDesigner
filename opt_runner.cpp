#include "opt_runner.h"



opt_runner::opt_runner(stl_config config, int seed)
{
	opt_runner::config = config;
	opt_runner::seed = seed;
	
	if (config.optimization_ == "ga") {
		algorithm = make_shared<ga_opt>(config, seed);
	}
	else {
		cerr << "undefined optimization type: " << config.optimization_ << "," << endl;
		cerr << "please correct the algorithm setting in your config file." << endl;
	}
}


opt_runner::~opt_runner()
{
}


void opt_runner::run()
{
	srand(seed);
	stl_initialize();
	algorithm->run();
}


void opt_runner::stl_initialize()
{
	
}
