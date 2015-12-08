#pragma once
class score_base
{
public:
	score_base();
	~score_base();
	void set(double row, double weight = 1.0);
	double row_weight_;
	double row_;
	double weight_;
	double ratio_;
	double ratio_weight_;
private:
};

