#include "blx_crossover.h"



blx_crossover::blx_crossover(stl_config config) : crossover_base(config)
{
}


blx_crossover::~blx_crossover()
{
}


vector<shared_ptr<stl>> blx_crossover::crossover(int generation, int offspring_num, shared_ptr<stl> parent1, shared_ptr<stl> parent2)
{
	vector<shared_ptr<stl>> offsprings(1);

	string name1 = "STL_gen" + to_string(generation) + "_offspring" + to_string(offspring_num) + config_.netlist_extension_;
	offsprings[0] = make_shared<stl>(name1, config_);

	vector<shared_ptr<sub_space>> subspaces1 = parent1->sub_spaces_;
	vector<shared_ptr<sub_space>> subspaces2 = parent2->sub_spaces_;

	vector<shared_ptr<sub_space>> new_subspaces;

	for (size_t i = 0; i < subspaces1.size(); i++) {
		shared_ptr<sub_space> new_subspace = make_shared<sub_space>(*subspaces1[i]);
		crossover_subspace(subspaces1[i], subspaces2[i], new_subspace);
		new_subspaces.push_back(new_subspace);
	}

	// “Ë‘R•ÏˆÙ
	if (stl_random::random_double(0, 100) < 5) {
		offsprings[0]->init_subspace();
		offsprings[0]->random_gene_assignment();
		cout << "mutation!" << endl;
	}
	else {
		offsprings[0]->gene_assignment(new_subspaces);
	}

	offsprings[0]->write_file();
	offsprings[0]->async_evaluate();

	return offsprings;
}


void blx_crossover::crossover_subspace(shared_ptr<sub_space> parent1, shared_ptr<sub_space> parent2,
	shared_ptr<sub_space> new_space)
{
	vector<double> segment_lengths1 = parent1->segment_lengths_;
	vector<int> segment_impedances1 = parent1->segment_impedances_;
	vector<double> segment_lengths2 = parent2->segment_lengths_;
	vector<int> segment_impedances2 = parent2->segment_impedances_;

	vector<double> new_segment_lengths;
	vector<int> new_segment_impedances;

	if (segment_lengths1.size() != segment_lengths2.size() || segment_impedances1.size() != segment_impedances2.size()
		|| segment_lengths1.size() != segment_impedances1.size()) {
		cerr << "segment num is not same!" << endl;
		exit(0);
	}

	new_segment_lengths = length_blx(segment_lengths1, segment_lengths2, new_space->maximum_length_);
	new_segment_impedances = impedance_blx(segment_impedances1, segment_impedances2);

	new_space->segment_lengths_ = new_segment_lengths;
	new_space->segment_impedances_ = new_segment_impedances;

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
