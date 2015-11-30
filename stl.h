#pragma once
#include "conventional.h"
class stl :
	public conventional
{
public:
	stl(stl_config config, shared_ptr<single_score> score);
	~stl();
	static shared_ptr<single_score> comparison_score_;
};

