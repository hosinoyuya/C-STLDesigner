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
	vector<shared_ptr<element>> elements = netlist_->stl_circuit_->elements_;
	shared_ptr<sub_space> sub;
	for (size_t i = 0; i < elements.size(); i++) {
		if (!elements[i]) continue;
		if (!stl_line::is_stl_element(elements[i])) continue;
		sub = make_shared<sub_space>(config_);
		sub->set_element(elements[i]);
		sub_spaces_.push_back(sub);
	}
}


void stl::random_gene_assignment()
{
	for (size_t i = 0; i < sub_spaces_.size(); i++) {
		sub_spaces_[i]->split();

	}
}