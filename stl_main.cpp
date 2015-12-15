#include "stl_main.h"

stl_main::stl_main(string file_name)
{
	config_.load(file_name);
	seeds_ = config_.seeds_;
}


stl_main::~stl_main()
{
}


void stl_main::run()
{
	cout << "------------------------------------------------------------------" << endl;
	cout << "------------------------- Start STL ------------------------------" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl;

	bool result, is_complete;
	for (size_t i = 0; i < config_.seeds_.size(); i++) {
		stl_config config_seed(config_);
		config_seed.chane_outdirectory_seed(config_.seeds_[i]);

		directory_init(config_seed);
		log_init(config_seed);

		result = run_optrunner(config_seed, config_.seeds_[i]);
		is_complete &= result;
	}

	cout << "------------------------------------------------------------------" << endl;
	cout << "----------------- STL Designer 2 has completed ! -----------------" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl;
}


void stl_main::directory_init(stl_config config)
{
	file_utils::rm_r(config.best_directory_);
	file_utils::rm_r(config.log_directory_);
	file_utils::mkdir(config.population_directory_);
	file_utils::mkdir(config.best_directory_);
	file_utils::mkdir(config.log_directory_);
}


void stl_main::log_init(stl_config config)
{
	population_log::init(config.log_directory_ + "/population.csv");
	best_log::init(config.log_directory_ + "/best_stls.csv");
}


bool stl_main::run_optrunner(stl_config config, int seed)
{
	cout << "------------------------- seed " << seed << " start ! -------------------------" << endl;
	cout << endl;

	opt_runner opt(config, seed);
	opt.run();

	cout << "---------------------- seed " << seed << " has compleated ! -------------------" << endl;
	cout << endl;
	return true;
}
