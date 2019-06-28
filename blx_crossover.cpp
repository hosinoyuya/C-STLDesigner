#include "blx_crossover.h"



blx_crossover::blx_crossover(stl_config config) : crossover_base(config)
{
	capacitor_nums = config.capacitor_nums_;
	cap_interval_change = config.cap_interval_change_;
	line_lengths = config.line_lengths_;
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

	int count = 0;
	int cap_place = 0;
	int subspace_num = 0;
	vector<double> length1 = {};
	vector<double> length2 = {};
	vector<double> cap_interval = {};
	vector<double> cap_intervals_ = {};
		
	if (cap_interval_change == 1) {
		for (int i = 0; i < subspaces1.size(); i++) {
			if (subspaces1[i]->element_type_ != C_ELEMENT) {
				length1.push_back(subspaces1[i]->segment_lengths_[0]);
				length2.push_back(subspaces2[i]->segment_lengths_[0]);
				count++;
			}
			if (count == capacitor_nums[cap_place] + 1) {
				cap_interval = length_blx(length1, length2, line_lengths[subspace_num]);
				cap_intervals_.insert(cap_intervals_.end(), cap_interval.begin(), cap_interval.end());
				count = 0;
				cap_place++;
				subspace_num++;
				length1.clear();
				length2.clear();
			}
		}
	}

	for (int i = 0; i < config_.brother_num_; i++) {
		vector<shared_ptr<sub_space>> new_subspaces;
		int line_sub = 0;
		for (size_t j = 0; j < subspaces1.size(); j++) {
			shared_ptr<sub_space> new_subspace = make_shared<sub_space>(*subspaces1[j]);
			if (subspaces1[j]->element_type_ != C_ELEMENT && cap_interval_change == 1) {
				crossover_subspace(subspaces1[j], subspaces2[j], cap_intervals_[line_sub], new_subspace);
				line_sub++;
			}
			else {
				crossover_subspace(subspaces1[j], subspaces2[j], 0, new_subspace);
			}
			new_subspaces.push_back(new_subspace);
		}

		mutation(offsprings[i], new_subspaces);

		offsprings[i]->write_file();
		offsprings[i]->async_evaluate();
	}

	return offsprings;
}


void blx_crossover::crossover_subspace(shared_ptr<sub_space> parent1, shared_ptr<sub_space> parent2, double cap_intervals,
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

	if (cap_interval_change == 1 && parent1->element_type_ != C_ELEMENT && parent2->element_type_ != C_ELEMENT) {
		new_space->segment_lengths_.push_back(cap_intervals);
	}
	else {
		new_space->segment_lengths_ = new_segment_lengths;
	}
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
	double maximum_capacitance = config_.maximum_capacitance_;
	double minimum_capacitance = config_.minimum_capacitance_;
	double capacitance_step = config_.capacitance_step_;
	vector<double> capacitance_values = config_.capacitance_values_;
	double new_capacitance;
	double capacitance_tmp = maximum_capacitance;

	for (size_t i = 0; i < parent1.size(); i++) {
		double p1 = parent1[i];
		double p2 = parent2[i];
		double deleta = fabs(p1 - p2);
		double range_max = max(p1, p2) + deleta * alpha;
		double range_min = min(p1, p2) - deleta * alpha;
		double cap_random = stl_random::random_double(range_min, range_max);
		for (int j = 0; j < capacitance_values.size(); j++) {
			double capacitance_diff = fabs(cap_random - capacitance_values[j]);
			if (capacitance_diff < capacitance_tmp) {
				capacitance_tmp = capacitance_diff;
				new_capacitance = capacitance_values[j];
			}
		}
		new_segment_capacitances.push_back(new_capacitance);
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