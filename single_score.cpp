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


string single_score::to_spice_comment()
{
	string return_string = "* score = " + to_string(value_) + "\n\n";
	for (size_t i = 0; i < point_scores_.size(); i++) {
		return_string += point_scores_[i]->to_spice_comment();
	}
	return return_string;
}


string single_score::to_str()
{
	return to_spice_comment();
}


void single_score::calc_ratio(shared_ptr<single_score> divisor)
{
	double score = 0.0;
	for (size_t i = 0; i < point_scores_.size(); i++) {
		shared_ptr<point_score> point_divisor = get_divisor(point_scores_[i]->point_, divisor->point_scores_);
		point_scores_[i]->calc_ratio(point_divisor);
		score += point_scores_[i]->ratio_weight_;
	}

	value_ = score / point_scores_.size();
}


shared_ptr<point_score> single_score::get_divisor(string point, vector<shared_ptr<point_score>> divisors)
{
	for (size_t i = 0; i < divisors.size(); i++) {
		if (divisors[i]->point_ == point) {
			return divisors[i];
		}
	}
	
	cerr << "calc_ratio error. not correct divisors" << endl;
	exit(0);
}
