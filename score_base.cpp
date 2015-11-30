#include "score_base.h"



score_base::score_base()
{
}


score_base::~score_base()
{
}


void score_base::set(double row, double weight)
{
	row_ = row;
	weight_ = weight;
	row_weight_ = row * weight;
}