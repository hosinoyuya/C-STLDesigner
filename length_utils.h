#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class length_utils
{
public:
	length_utils();
	~length_utils();
	static void shift_overlap(vector<double>& rand_array, double item_min);
	static void shift_overlap_reverse(vector<double>& rand_array, double item_min, double range_max);
	static vector<double> get_segment_length_array(vector<double> split_array, double item_sum);
	static vector<double> get_split_array(vector<double> segment_length_array);
};

