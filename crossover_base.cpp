#include "crossover_base.h"



crossover_base::crossover_base(stl_config config)
{
	config_ = config;
}


crossover_base::~crossover_base()
{
}


vector<double> crossover_base::ajust_length(vector<double> lengths, double ajust_length)
{
	double length = accumulate(lengths.begin(), lengths.end(), 0.0);
	double magnification = ajust_length / length;

	vector<double> new_lengths(lengths.size());

	for (size_t i = 0; i < lengths.size(); i++) {
		new_lengths[i] = lengths[i] * magnification;	
	}

	return ajust_small_segment(new_lengths, ajust_length);
}


vector<double> crossover_base::ajust_small_segment(vector<double> lengths, double ajust_length)
{
	double minimum_length = config_.minimum_length_;

	// ¬‚³‚·‚¬‚éƒZƒOƒƒ“ƒg‚ğL‚°‚é
	vector<double> split_array = length_utils::get_split_array(lengths);
	length_utils::shift_overlap(split_array, minimum_length);
	length_utils::shift_overlap_reverse(split_array, minimum_length, ajust_length);
	vector<double> new_lengths = length_utils::get_segment_length_array(split_array, ajust_length);

	return new_lengths;
}
