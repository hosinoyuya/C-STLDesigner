#include "transient_wave.h"

const int EFFECTIVE_DIGIT = 11;

transient_wave::transient_wave(shared_ptr<node_point> point)
{
	point_ = point;
}


transient_wave::~transient_wave()
{
}

void transient_wave::generate_time_division(vector<double> time_division)
{
	time_division_ = time_division;
	time_begin_ = time_division[0];
	time_end_ = time_division[time_division.size() - 1];
	time_interval_ = time_division[1] - time_division[0];
}


size_t transient_wave::size()
{
	return time_division_.size();
}