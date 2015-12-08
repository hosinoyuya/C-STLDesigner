#pragma once
#include "score_base.h"
#include <string>
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
	string point_;
	string method_;
private:
};

