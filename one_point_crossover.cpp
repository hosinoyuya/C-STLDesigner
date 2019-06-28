#include "one_point_crossover.h"



one_point_crossover::one_point_crossover(stl_config config) : crossover_base(config)
{
}


one_point_crossover::~one_point_crossover()
{
}



vector<shared_ptr<stl>> one_point_crossover::crossover(int generation, int offspring_num, shared_ptr<stl> parent1, shared_ptr<stl> parent2)
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

	vector<double> capacitances1;
	vector<double> capacitances2;
	vector<double> capacitance_tmp;
	int subspace_size = subspaces1.size();

	cout << "one_point" << endl;

	if (subspaces1[0]->element_type_ == C_ELEMENT) {
		for (int i = 0; i < subspace_size; i++) {
			capacitances1.push_back(subspaces1[i]->segment_capacitances_[0]);
			capacitances2.push_back(subspaces2[i]->segment_capacitances_[0]);
			//cout << capacitances1[i] << "," << capacitances2[i] << endl;
		}

		int cross_point1 = stl_random::random_int(0, subspace_size-2);
		int cross_point2 = stl_random::random_int(cross_point1, subspace_size-1);
		
		for (int j = cross_point1; j < cross_point2; j++) {
			capacitance_tmp.push_back(capacitances1[j]);
			capacitances1[j] = capacitances2[j];
			capacitances2[j] = capacitance_tmp[j-cross_point1];
		}
		//cout << cross_point1 << "," << cross_point2 << endl;
		for (int k = 0; k < subspace_size; k++) {
			subspaces1[k]->segment_capacitances_[0] = capacitances1[k];
			subspaces2[k]->segment_capacitances_[0] = capacitances2[k];

			//cout << capacitances1[k] << "," << capacitances2[k] << endl;

			new_subspaces1.push_back(subspaces1[k]);
			new_subspaces2.push_back(subspaces2[k]);
		}

	}
	else {
		for (size_t i = 0; i < subspaces1.size(); i++) {
			shared_ptr<sub_space> new_subspace1 = make_shared<sub_space>(*subspaces1[i]);
			shared_ptr<sub_space> new_subspace2 = make_shared<sub_space>(*subspaces2[i]);

			crossover_subspace(subspaces1[i], subspaces2[i], new_subspace1, new_subspace2);

			new_subspaces1.push_back(new_subspace1);
			new_subspaces2.push_back(new_subspace2);
		}
	}

	// “Ë‘R•ÏˆÙ
	if (stl_random::random_int(0, 99) < 10) {
		offsprings[0]->init_subspace();
		offsprings[0]->random_gene_assignment();
		cout << "mutation!" << endl;
	}
	else {
		offsprings[0]->gene_assignment(new_subspaces1);
	}
	offsprings[0]->write_file();
	offsprings[1]->gene_assignment(new_subspaces2);
	offsprings[1]->write_file();

	offsprings[0]->async_evaluate();
	offsprings[1]->async_evaluate();

	return offsprings;
}


void one_point_crossover::crossover_subspace(shared_ptr<sub_space> parent1, shared_ptr<sub_space> parent2,
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

	int cut_point;
	if (segment_lengths1.size() == 1) {
		cut_point = 0;
	}
	else {
		cut_point = stl_random::random_int(1, segment_lengths1.size() - 1);
	}

	copy(segment_lengths1.begin(), segment_lengths1.begin() + cut_point, back_inserter(new_segment_lengths1));
	copy(segment_lengths2.begin() + cut_point, segment_lengths2.end(), back_inserter(new_segment_lengths1));
	copy(segment_lengths2.begin(), segment_lengths2.begin() + cut_point, back_inserter(new_segment_lengths2));
	copy(segment_lengths1.begin() + cut_point, segment_lengths1.end(), back_inserter(new_segment_lengths2));

	copy(segment_impedances1.begin(), segment_impedances1.begin() + cut_point, back_inserter(new_segment_impedances1));
	copy(segment_impedances2.begin() + cut_point, segment_impedances2.end(), back_inserter(new_segment_impedances1));
	copy(segment_impedances2.begin(), segment_impedances2.begin() + cut_point, back_inserter(new_segment_impedances2));
	copy(segment_impedances1.begin() + cut_point, segment_impedances1.end(), back_inserter(new_segment_impedances2));

	new_segment_lengths1 = ajust_length(new_segment_lengths1, new_space1->maximum_length_);
	new_segment_lengths2 = ajust_length(new_segment_lengths2, new_space2->maximum_length_);

	new_space1->segment_lengths_ = new_segment_lengths1;
	new_space1->segment_impedances_ = new_segment_impedances1;
	new_space2->segment_lengths_ = new_segment_lengths2;
	new_space2->segment_impedances_ = new_segment_impedances2;

	new_space1->split();
	new_space2->split();
}

