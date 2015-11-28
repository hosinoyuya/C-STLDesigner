#pragma once
#include "node_point.h"
#include <memory>
#include <vector>

using namespace std;

class transient_wave
{
public:
	transient_wave(shared_ptr<node_point> point);
	~transient_wave();
	vector<string> time_division;
	vector<string> voltage;
private:
	shared_ptr<node_point> point_;
};

