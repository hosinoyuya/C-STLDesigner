#include "blx_crossover.h"



blx_crossover::blx_crossover(stl_config config) : crossover_base(config)
{
}


blx_crossover::~blx_crossover()
{
}


vector<shared_ptr<stl>> blx_crossover::crossover(int generation, int offspring_num, shared_ptr<stl> parent1, shared_ptr<stl> parent2)
{
	vector<shared_ptr<stl>> offsprings;

	for (int i = 0; i < config_.brother_num_; i++) {
		string name = "STL_gen" + to_string(generation) + "_offspring" + to_string(offspring_num)
			+ "_" + to_string(i) + config_.netlist_extension_;
		offsprings.push_back(make_shared<stl>(name, config_));
	}
	vector<shared_ptr<sub_space>> subspaces1 = parent1->sub_spaces_;
	vector<shared_ptr<sub_space>> subspaces2 = parent2->sub_spaces_;

	for (int i = 0; i < config_.brother_num_; i++) {
		vector<shared_ptr<sub_space>> new_subspaces;
		for (size_t j = 0; j < subspaces1.size(); j++) {
			shared_ptr<sub_space> new_subspace = make_shared<sub_space>(*subspaces1[j]);
			crossover_subspace(subspaces1[j], subspaces2[j], new_subspace);
			new_subspaces.push_back(new_subspace);
		}

		mutation(offsprings[i], new_subspaces);

		offsprings[i]->write_file();
		offsprings[i]->async_evaluate();
	}

	return offsprings;
}


void blx_crossover::crossover_subspace(shared_ptr<sub_space> parent1, shared_ptr<sub_space> parent2,
	shared_ptr<sub_space> new_space)
{
	vector<double> segment_lengths1 = parent1->segment_lengths_;
	vector<int> segment_impedances1 = parent1->segment_impedances_;
	vector<double> segment_capacitances1 = parent1->segment_capacitances_;
	vector<double> segment_lengths2 = parent2->segment_lengths_;
	vector<int> segment_impedances2 = parent2->segment_impedances_;
	vector<double> segment_capacitances2 = parent2->segment_capacitances_;

	vector<double> new_segment_lengths;
	vector<int> new_segment_impedances;
	vector<double> new_segment_capacitances;

	if (segment_lengths1.size() != segment_lengths2.size() || segment_impedances1.size() != segment_impedances2.size()
		|| segment_lengths1.size() != segment_impedances1.size() || segment_capacitances1.size() != segment_capacitances2.size()) {
		cerr << "segment num is not same!" << endl;
		exit(0);
	}

	if (parent1->element_type_ == C_ELEMENT && parent2->element_type_ == C_ELEMENT) {
		new_segment_capacitances = capacitance_blx(segment_capacitances1, segment_capacitances2);
	}
	else {
		new_segment_lengths = length_blx(segment_lengths1, segment_lengths2, new_space->maximum_length_);
		new_segment_impedances = impedance_blx(segment_impedances1, segment_impedances2);
	}

	new_space->segment_lengths_ = new_segment_lengths;
	new_space->segment_impedances_ = new_segment_impedances;
	new_space->segment_capacitances_ = new_segment_capacitances;

	new_space->split();
}


vector<double> blx_crossover::length_blx(vector<double> parent1, vector<double> parent2, double total_length)
{
	vector<double> new_segment_lengths;

	double alpha = config_.blx_alpha_;
	double minimum_length = config_.minimum_length_;

	for (size_t i = 0; i < parent1.size(); i++) {
		double deleta = fabs(parent1[i] - parent2[i]);
		double range_max = max(parent1[i], parent2[i]) + deleta * alpha;
		double range_min = min(parent1[i], parent2[i]) - deleta * alpha;
		range_min = max(minimum_length, range_min);
		new_segment_lengths.push_back(stl_random::random_double(range_min, range_max));
	}

	double length_before_last = accumulate(new_segment_lengths.begin(), new_segment_lengths.end() - 1, 0.0);
	double last_length = total_length - length_before_last;

    if (last_length > config_.minimum_length_) {
        new_segment_lengths[new_segment_lengths.size() - 1] = last_length;
	    return ajust_small_segment(new_segment_lengths, total_length);
    } else {
	    return length_blx(parent1, parent2, total_length);
    }
}


vector<int> blx_crossover::impedance_blx(vector<int> parent1, vector<int> parent2)
{
	vector<int> new_segment_impedances;

	double alpha = config_.blx_alpha_;
	int maximum_impedance = config_.maximum_inpedance_;
	int minimum_impedance = config_.minimum_inpedance_;
	int inpedance_step = config_.impedance_step_;

	for (size_t i = 0; i < parent1.size(); i++) {
		double deleta = fabs(parent1[i] - parent2[i]);
		double range_max = (double)max(parent1[i], parent2[i]) + deleta * alpha;
		double range_min = (double)min(parent1[i], parent2[i]) - deleta * alpha;
		double double_random = stl_random::random_double(range_min, range_max);
		int new_impedance = (int)round(double_random / inpedance_step) * inpedance_step;
		if (new_impedance > maximum_impedance) {
			new_impedance = maximum_impedance;
		}
		else if (new_impedance < minimum_impedance) {
			new_impedance = minimum_impedance;
		}

		new_segment_impedances.push_back(new_impedance);
	}

	return new_segment_impedances;
}


vector<double> blx_crossover::capacitance_blx(vector<double> parent1, vector<double> parent2)
{
	vector<double> new_segment_capacitances;

	double alpha = config_.blx_alpha_;
	int maximum_capacitance = config_.maximum_capacitance_*1e12;
	int minimum_capacitance = config_.minimum_capacitance_*1e12;
	int capacitance_step = config_.capacitance_step_*1e12;

	for (size_t i = 0; i < parent1.size(); i++) {
		double oya1 = parent1[i] * 1e12;
		double oya2 = parent2[i] * 1e12;
		double deleta = fabs(oya1 - oya2);
		double range_max = (double)max(oya1, oya2) + deleta * alpha;
		double range_min = (double)min(oya1, oya2) - deleta * alpha;
		double double_random = stl_random::random_double(range_min, range_max);
		int new_capacitance = (int)round(double_random / capacitance_step) * capacitance_step;
		if (new_capacitance > maximum_capacitance) {
			new_capacitance = maximum_capacitance;
		}
		else if (new_capacitance < minimum_capacitance) {
			new_capacitance = minimum_capacitance;
		}

		new_segment_capacitances.push_back(new_capacitance*1e-12);
	}

	return new_segment_capacitances;
}


void blx_crossover::mutation(shared_ptr<stl> &offspring, vector<shared_ptr<sub_space>> &new_subspaces)
{
	// 突然変異
	if (stl_random::random_double(0, 100) < config_.mutation_ * 100) {
		if (config_.mutation_type_ == "all") {
			offspring->init_subspace();
			offspring->random_gene_assignment();
		}
		else if (config_.mutation_type_ == "one_point") {
			int change_space = stl_random::random_int(0, new_subspaces.size() - 1);
			int change_pos = stl_random::random_int(0, new_subspaces[change_space]->segment_impedances_.size() - 1);
			new_subspaces[change_space]->segment_impedances_[change_pos] =
				stl_random::frand_between(config_.minimum_inpedance_, config_.maximum_inpedance_, config_.impedance_step_);
			new_subspaces[change_space]->segment_lengths_[change_pos] =
				stl_random::random_double(config_.minimum_length_, new_subspaces[change_space]->maximum_length_ - config_.minimum_length_);
			new_subspaces[change_space]->segment_lengths_ =
				ajust_small_segment(new_subspaces[change_space]->segment_lengths_, new_subspaces[change_space]->maximum_length_);
			offspring->gene_assignment(new_subspaces);
		}
		else {
			offspring->init_subspace();
			offspring->random_gene_assignment();
		}
		cout << "mutation!" << endl;
	}
	else {
		offspring->gene_assignment(new_subspaces);
	}
}