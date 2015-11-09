#include "ga_opt.h"



ga_opt::ga_opt(stl_config config, int seed)
{
	ga_opt::config = config;
	ga_opt::seed = seed;
}


ga_opt::~ga_opt()
{
}


void ga_opt::run()
{
	cout << "ga running!" << endl;
}
