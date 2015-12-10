#include "uniform_crossover.h"



uniform_crossover::uniform_crossover(stl_config config)
{
	config_ = config;
}


uniform_crossover::~uniform_crossover()
{
}


vector<shared_ptr<stl>> uniform_crossover::crossover(int generation, int offspring_num, shared_ptr<stl> parent1, shared_ptr<stl> parent2)
{
	vector<shared_ptr<stl>> offsprings(2);

	string name1 = "STL_gen" + to_string(generation) + "_offspring" + to_string(offspring_num) + "_1" + config_.netlist_extension_;
	string name2 = "STL_gen" + to_string(generation) + "_offspring" + to_string(offspring_num) + "_2" + config_.netlist_extension_;
	offsprings[0] = make_shared<stl>(name1, config_);
	offsprings[1] = make_shared<stl>(name2, config_);

	vector<shared_ptr<sub_space>> subspaces1 = parent1->sub_spaces_;
	vector<shared_ptr<sub_space>> subspaces2 = parent2->sub_spaces_;

	vector<shared_ptr<sub_space>> new_subspaces1;
	vector<shared_ptr<sub_space>> new_subspaces2;

	for (size_t i = 0; i < subspaces1.size(); i++) {
		shared_ptr<sub_space> new_subspace1 = make_shared<sub_space>(*subspaces1[i]);
		shared_ptr<sub_space> new_subspace2 = make_shared<sub_space>(*subspaces2[i]);

		crossover_subspace(subspaces1[i], subspaces2[i], new_subspace1, new_subspace2);

		new_subspaces1.push_back(new_subspace1);
		new_subspaces2.push_back(new_subspace2);
	}

	offsprings[0]->gene_assignment(new_subspaces1);
	offsprings[0]->write_file();
	offsprings[1]->gene_assignment(new_subspaces2);
	offsprings[1]->write_file();

	offsprings[0]->evaluate();
	offsprings[1]->evaluate();

	return offsprings;
}


void uniform_crossover::crossover_subspace(shared_ptr<sub_space> parent1, shared_ptr<sub_space> parent2,
	shared_ptr<sub_space> new_space1, shared_ptr<sub_space> new_space2)
{
	vector<double> segment_lengths1 = parent1->segment_lengths_;
	vector<int> segment_impedances1 = parent1->segment_impedances_;
	vector<double> segment_lengths2 = parent2->segment_lengths_;
	vector<int> segment_impedances2 = parent2->segment_impedances_;

	vector<double> new_segment_lengths1;
	vector<int> new_segment_impedances1;
	vector<double> new_segment_lengths2;
	vector<int> new_segment_impedances2;

	if (segment_lengths1.size() != segment_lengths2.size() || segment_impedances1.size() != segment_impedances2.size()
		|| segment_lengths1.size() != segment_impedances1.size()) {
		cerr << "segment num is not same!" << endl;
		exit(0);
	}

	for (size_t i = 0; i < segment_lengths1.size(); i++) {
		if (stl_random::random_int(0, 1)) {
			new_segment_lengths1.push_back(segment_lengths1[i]);
			new_segment_lengths2.push_back(segment_lengths2[i]);
			new_segment_impedances1.push_back(segment_impedances1[i]);
			new_segment_impedances2.push_back(segment_impedances2[i]);
		}
		else {
			new_segment_lengths1.push_back(segment_lengths2[i]);
			new_segment_lengths2.push_back(segment_lengths1[i]);
			new_segment_impedances1.push_back(segment_impedances2[i]);
			new_segment_impedances2.push_back(segment_impedances1[i]);
		}
	}

	new_segment_lengths1 = ajust_length(new_segment_lengths1, new_space1->maximum_length_);
	new_segment_lengths2 = ajust_length(new_segment_lengths2, new_space2->maximum_length_);

	new_space1->segment_lengths_ = new_segment_lengths1;
	new_space1->segment_impedances_ = new_segment_impedances1;
	new_space2->segment_lengths_ = new_segment_lengths2;
	new_space2->segment_impedances_ = new_segment_impedances2;

	new_space1->split();
	new_space2->split();
}


vector<double> uniform_crossover::ajust_length(vector<double> lengths, double ajust_length)
{
	double length = accumulate(lengths.begin(), lengths.end(), 0.0);
	double magnification = ajust_length / length;

	vector<double> new_lengths(lengths.size());
	for (size_t i = 0; i < lengths.size(); i++) {
		new_lengths[i] = lengths[i] * magnification;
	}

	return new_lengths;
}