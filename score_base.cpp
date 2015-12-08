#include "score_base.h"

const double INIT_SCORE = 999999999;

score_base::score_base()
{
	ratio_ = INIT_SCORE;
	ratio_weight_ = INIT_SCORE;
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