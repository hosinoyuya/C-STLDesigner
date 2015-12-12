#include "length_utils.h"



length_utils::length_utils()
{
}


length_utils::~length_utils()
{
}


void length_utils::shift_overlap(vector<double>& rand_array, double item_min)
{
	//vector<double> return_val;
	if (rand_array[0] < item_min) {
		rand_array[0] = item_min;
	}
	for (size_t i = 0; i < rand_array.size() - 1; i++) {
		if ((rand_array[i + 1] - rand_array[i]) < item_min) {
			rand_array[i+1] = rand_array[i] + item_min;
		}
	}
}


void length_utils::shift_overlap_reverse(vector<double>& rand_array, double item_min, double range_max)
{
	if ((range_max - rand_array[rand_array.size() - 1]) < item_min) {
		rand_array[rand_array.size() - 1] = range_max - item_min;
	}
	for (size_t i = rand_array.size() - 1; i > 0; i--) {
		if ((rand_array[i] - rand_array[i - 1]) < item_min) {
			rand_array[i - 1] = rand_array[i] - item_min;
		}
	}
}


vector<double> length_utils::get_segment_length_array(vector<double> split_array, double item_sum)
{
	vector<double> segment_length_array;
	split_array.push_back(item_sum);
	segment_length_array.push_back(split_array[0]);
	for (size_t i = 0; i < split_array.size()-1; i++) {
		segment_length_array.push_back(split_array[i + 1] - split_array[i]);
	}
	return segment_length_array;
}


vector<double> length_utils::get_split_array(vector<double> segment_length_array) {
	vector<double> split_array;
	double split_position = 0.0;
	for (size_t i = 0; i < segment_length_array.size() - 1; i++) {
		split_position += segment_length_array[i];
		split_array.push_back(split_position);
	}
	return split_array;
}