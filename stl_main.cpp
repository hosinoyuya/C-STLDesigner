#include "stl_main.h"

stl_main::stl_main(string file_name)
{
	config.load(file_name);
	seeds = config.seeds_;
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

	for (size_t i = 0; i < config.seeds_.size(); i++) {
		bool is_complete = true;
		stl_config config_seed(config);
		config_seed.chane_outdirectory_seed(config.seeds_[i]);
		
		directory_init(config_seed);

	}

	cout << "------------------------------------------------------------------" << endl;
	cout << "----------------- STL Designer 2 has completed ! -----------------" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl;
}


void stl_main::directory_init(stl_config config)
{
	file_utils::rm_r(config.population_directory_);
	file_utils::rm_r(config.best_directory_);
	file_utils::rm_r(config.log_directory_);
	file_utils::mkdir(config.population_directory_);
	file_utils::mkdir(config.best_directory_);
	file_utils::mkdir(config.log_directory_);
}
