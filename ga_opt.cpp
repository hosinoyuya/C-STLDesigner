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
	shared_ptr<stl> stl_random;
	for (int i = 0; i < config_.population_size_; i++) {
		name = "STL_init_candidate" + to_string(i) + config_.netlist_extension_;
		stl_random = make_shared<stl>(name, config_);
		stl_random->init_subspace();
		stl_random->random_gene_assignment();
		stl_random->write_file();
		stl_random->evaluate();
		population_.push_back(stl_random);
	}

	shared_ptr<stl> best = select_best();
	best->file_copy_to(config_.best_directory_);
}


shared_ptr<stl> ga_opt::select_best()
{
	sort(population_.begin(), population_.end(),
		[](const shared_ptr<stl> &left, const shared_ptr<stl> &right) {
		return left->score_->value_ < right->score_->value_;
	});

	return population_[0];
}