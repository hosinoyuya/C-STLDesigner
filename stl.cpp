#include "stl.h"

// STLオブジェクトに番号を振るためのバッファ
static int num = 0;
bool stl::simulation_failed_flag_ = false;
vector<shared_ptr<thread>> stl::threads_;

stl::stl(string file_name, stl_config config, shared_ptr<single_score> score) : conventional(file_name, config, score)
{
	file_path_ = config.population_directory_ + "/" + file_name;
	index_ = num;
	num++;
	netlist_ = make_shared<netlist_base>(*template_);
	netlist_->file_path_ = file_path_;
	best_flag_ = false;
}


stl::~stl()
{
	for (size_t i = 0; i < config_.spice_extensions_.size(); i++) {
		string delete_file_path = boost::algorithm::replace_all_copy(file_path_, config_.netlist_extension_, config_.spice_extensions_[i]);
		file_utils::rm(delete_file_path);
	}
}


void stl::init_subspace()
{
	list<shared_ptr<element>> elements = netlist_->stl_circuit_->elements_;
	shared_ptr<sub_space> sub;
	list<shared_ptr<element>>::iterator element_itr = elements.begin();
	while (element_itr != elements.end()) {
		if (!(*element_itr)) {
			element_itr++;
			continue;
		}
		if (!stl_line::is_stl_element((*element_itr))) {
			element_itr++;
			continue;
		}
		sub = make_shared<sub_space>(config_);
		sub->set_element((*element_itr));
		sub_spaces_.push_back(sub);
		element_itr++;
	}
}


void stl::random_gene_assignment()
{
	netlist_->stl_circuit_->copy_default_contents();
	for (size_t i = 0; i < sub_spaces_.size(); i++) {
		sub_spaces_[i]->split_random();
		netlist_->stl_circuit_->exchange_subspace(sub_spaces_[i]);
	}
}


void stl::gene_assignment(vector<shared_ptr<sub_space>> gene)
{
	sub_spaces_ = gene;
	netlist_->stl_circuit_->copy_default_contents();
	for (size_t i = 0; i < sub_spaces_.size(); i++) {
		netlist_->stl_circuit_->exchange_subspace(sub_spaces_[i]);
	}
}


void stl::write_file()
{
	netlist_->write(file_path_);
}


void stl::evaluate()
{
	if (!simulate()) {
        simulation_failed_flag_ = true;
        return;
    }
	set_waves();
	set_scores(comparison_score_);
	netlist_->write_score(score_);
}


void stl::async_evaluate() {
	if (config_.use_multithread_ && hspice::use_multiserver_) {
		shared_ptr<thread> evaluate_thread = make_shared<thread>(&stl::evaluate, this);
		threads_.push_back(evaluate_thread);
	}
	else {
		stl_timer::evaluate_start();
		evaluate();
		stl_timer::evaluate_stop();
	}
}


void stl::join_evaluate() {
	stl_timer::evaluate_start();
	for (size_t i = 0; i < threads_.size(); i++) {
		threads_[i]->join();
	}
	threads_.clear();
	stl_timer::evaluate_stop();
}
