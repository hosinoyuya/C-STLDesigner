#pragma once
#include "normal_ga.h"
#include "stl_config.h"
#include "stl.h"
#include "stl_random.h"
#include <memory>
#include <vector>
#include <float.h>

class mgg :
	public normal_ga
{
public:
	mgg(stl_config config);
	~mgg();
	void change(int generation, vector<shared_ptr<stl>>& population);
private:
	shared_ptr<stl> extract_elete(vector<shared_ptr<stl>>& population);
	shared_ptr<stl> extract_random(vector<shared_ptr<stl>>& population);
};

