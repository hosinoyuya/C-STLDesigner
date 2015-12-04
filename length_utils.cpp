#include "length_utils.h"



length_utils::length_utils()
{
}


length_utils::~length_utils()
{
}


vector<double> length_utils::shift_overlap(vector<double> rand_array, double item_min)
{
	vector<double> return_val;
	if (rand_array[0] <= item_min) {
		return_val.push_back(item_min);
	}
	else {
		return_val.push_back(rand_array[0]);
	}
	for (size_t i = 0; i < rand_array.size() - 1; i++) {
		if ((rand_array[i + 1] - rand_array[i]) <= item_min) {
			return_val.push_back(rand_array[i] + item_min);
		}
		else {
			return_val.push_back(rand_array[i + 1]);
		}
	}
	return return_val;
}


vector<double> length_utils::shift_overlap_reverse(vector<double> rand_array, double item_min, double range_max)
{
	vector<double> return_val;
	if ((range_max - rand_array[rand_array.size() - 1]) <= item_min) {
		return_val.push_back(range_max - item_min);
	}
	else {
		return_val.push_back(rand_array[rand_array.size() - 1]);
	}
	for (size_t i = rand_array.size() - 1; i > 0; i--) {
		if ((rand_array[i] - rand_array[i - 1]) <= item_min) {
			return_val.push_back(rand_array[i] - item_min);
		}
		else {
			return_val.push_back(rand_array[i - 1]);
		}
	}
	reverse(return_val.begin(), return_val.end());
	return return_val;
}


vector<double> length_utils::get_segment_length_array(vector<double> rand_array, double item_sum)
{
	vector<double> return_val;
	rand_array.push_back(item_sum);
	return_val.push_back(rand_array[0]);
	for (size_t i = 0; i < rand_array.size()-1; i++) {
		return_val.push_back(rand_array[i + 1] - rand_array[i]);
	}
	return return_val;
}
