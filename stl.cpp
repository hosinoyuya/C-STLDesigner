#include "stl.h"

// STLオブジェクトに番号を振るためのバッファ
static int num = 0;

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
	for (size_t i = 0; i < sub_spaces_.size(); i++) {
		sub_spaces_[i]->split();
		netlist_->stl_circuit_->exchange_subspace(sub_spaces_[i]);
	}
}


void stl::write_file()
{
	netlist_->write(file_path_);
}


void stl::evaluate()
{
	simulate();
	set_waves();
	set_scores(comparison_score_);
	netlist_->write_score(score_);
}