#pragma once
#include "score_base.h"
#include <string>

using namespace std;

class point_score :
	public score_base
{
public:
	point_score(string point, string method);
	~point_score();
private:
	string point_;
	string method_;
};

