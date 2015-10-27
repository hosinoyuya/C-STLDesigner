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

	for (int i = 0; i < config.seeds_.size(); i++) {
		bool is_complete = true;
		stl_config config_seed(config);
		config_seed.chane_outdirectory_seed(config.seeds_[i]);
		
	}

	cout << "------------------------------------------------------------------" << endl;
	cout << "----------------- STL Designer 2 has completed ! -----------------" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << endl;
}
