#include "single_score.h"



single_score::single_score()
{
}


single_score::~single_score()
{
}


void single_score::set(vector<shared_ptr<point_score>> point_scores)
{
	point_scores_ = point_scores;

	double score = 0;
	for (size_t i = 0; i < point_scores_.size(); i++) {
		score += point_scores_[i]->row_weight_;
	}

	value_ = score;
}