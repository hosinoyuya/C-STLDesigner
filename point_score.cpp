#include "point_score.h"



point_score::point_score(string point, string method)
{
	point_ = point;
	method_ = method;
}


point_score::~point_score()
{
}


string point_score::to_spice_comment()
{
	string return_string = "* PointScore ***\n";
	return_string += "* function = " + method_ + "\n";
	return_string += "* node = " + point_ + "\n\n";
	return return_string;
}


void point_score::calc_ratio(shared_ptr<point_score> divisor)
{
	ratio_ = row_ / divisor->row_;
	ratio_weight_ = ratio_ / weight_;
}


void point_score::set_eye_info(vector<vector<double>> eye_diagram, double eye_width, double eye_height)
{
	eye_diagram_ = eye_diagram;
	eye_width_ = eye_width;
	eye_height_ = eye_height;
}