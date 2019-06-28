#include "length_utils.h"



length_utils::length_utils()
{
}


length_utils::~length_utils()
{
}


void length_utils::shift_overlap(vector<double>& rand_array, double item_min)
{
	double before_point = 0;
	for (size_t i = 0; i < rand_array.size(); i++) {
		if ((rand_array[i] - before_point) < item_min) {
			rand_array[i] = before_point + item_min;
		}
		before_point = rand_array[i];
	}
}


void length_utils::shift_overlap_reverse(vector<double>& rand_array, double item_min, double range_max)
{
	double after_point = range_max;
	for (size_t i = rand_array.size(); i > 0; i--) {
		if ((after_point - rand_array[i-1]) < item_min) {
			rand_array[i-1] = after_point - item_min;
		}
		after_point = rand_array[i-1];
	}
}


vector<double> length_utils::get_segment_length_array(vector<double> split_array, double item_sum)
{
	vector<double> segment_length_array;
	split_array.push_back(item_sum);
	double before_point = 0;
	for (size_t i = 0; i < split_array.size(); i++) {
		segment_length_array.push_back(split_array[i] - before_point);
		before_point = split_array[i];
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