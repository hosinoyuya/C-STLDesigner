#include "score_base.h"

const double INIT_SCORE = 999999999;

score_base::score_base()
{
	ratio_ = INIT_SCORE;
	ratio_weight_ = INIT_SCORE;
	shift_ = 0;
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

void score_base::set_weight(double weight)
{
	weight_ = weight;
	row_weight_ = row_ * weight;
}