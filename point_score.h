#pragma once
#include "score_base.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class point_score :
	public score_base
{
public:
	point_score(string point, string method);
	~point_score();
	string to_spice_comment();
	void calc_ratio(shared_ptr<point_score> divisor);
	void set_eye_info(vector<vector<double>> eye_diagram, double eye_width, double eye_height);
	string point_;
	string method_;
	vector<vector<double>> eye_diagram_;
	double eye_width_;
	double eye_height_;
private:
};

