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

	loop_ga();
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
		stl_random->async_evaluate();
		population_.push_back(stl_random);
	}

	stl::join_evaluate();
    // Š„‚è‚İ‚ª”­¶‚µ‚½ê‡C‚Ü‚½‚ÍChspice‚ª“r’†‚Å’â~‚µ‚½ê‡
	// ”ñ“¯Šúˆ—‚ªI‚í‚Á‚½“_‚ÅƒT[ƒo[‚ğ’â~‚³‚¹exit
    if (stl_signal::signal_flag_ || stl::simulation_failed_flag_) {
        hspice::delete_server();
        exit(0);
    }

	shared_ptr<stl> best = select_best();
	best->file_copy_to(config_.best_directory_);

	log_generation(0, best);
}


void ga_opt::loop_ga()
{
	normal_ga nga(config_);

	double now_best = 100;
	for (int generation = 1; generation < config_.generation_num_; generation++) {
		cout << "######### generation " << generation << " #########" << endl;

		nga.clear();
		nga.change(generation, population_);

		shared_ptr<stl> best = select_best();
		if (now_best > best->score_->value_) {
			now_best = best->score_->value_;
			best->file_copy_to(config_.best_directory_);
		}

		log_generation(generation, best);
	}
}



shared_ptr<stl> ga_opt::select_best()
{
	sort(population_.begin(), population_.end(),
		[](const shared_ptr<stl> &left, const shared_ptr<stl> &right) {
		return left->score_->value_ < right->score_->value_;
	});

	return population_[0];
}

void ga_opt::log_generation(int generation, shared_ptr<stl> best)
{
	cout << endl << " --- Now best score stl ---" << endl;
	cout << best->name_ << " : " << best->score_->value_ << endl;
	cout << endl;

	vector<shared_ptr<stl>> vector_best;
	vector_best.push_back(best);
	best_log::puts_stl(generation, vector_best);
	population_log::puts_stl(generation, population_);

	population_log::lotation(generation, config_.lotation_step_);
}
