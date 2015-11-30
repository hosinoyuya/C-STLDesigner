#pragma once
#include "point_score.h"
#include <vector>
#include <memory>

using namespace std;

class single_score
{
public:
	single_score();
	~single_score();
	void set(vector<shared_ptr<point_score>> point_scores);
private:
	vector<shared_ptr<point_score>> point_scores_;
	double value_;
};

