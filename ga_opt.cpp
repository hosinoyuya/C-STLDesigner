#include "ga_opt.h"



ga_opt::ga_opt(stl_config config, int seed)
{
	ga_opt::config_ = config;
	ga_opt::seed_ = seed;
}


ga_opt::~ga_opt()
{
}


void ga_opt::run()
{
	cout << "------------ initialize candidate stl (generation 0) -------------" << endl;

	generate_random_stl();

	cout << "----------------------------- GA loop ----------------------------" << endl;
}


void ga_opt::generate_random_stl()
{
	string name;
	shared_ptr<stl> stl_buf;
	for (int i = 0; i < config_.population_size_; i++) {
		name = "STL_init_candidate" + to_string(i) + config_.netlist_extension_;
		stl_buf = make_shared<stl>(name, config_);
		stl_buf->init_subspace();
		stl_buf->random_gene_assignment();
		stl_buf->write_file();
		
	}
}