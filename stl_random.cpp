#include "stl_random.h"

mt19937 stl_random::mt;

stl_random::stl_random()
{
}


stl_random::~stl_random()
{
}


void stl_random::srand(unsigned int seed)
{
	mt.seed(seed);
}


int stl_random::random_int(int max, int min)
{
	std::uniform_int_distribution<int> rand(max, min);
	return rand(mt);
}


double stl_random::random_double(double max, double min)
{
	std::uniform_real_distribution<double> rand(max, min);
	return rand(mt);
}


int stl_random::frand_between(int min, int max, int step)
{
	int range = max - min;
	int num = range / step;
	int rand = random_int(0, num);
	return min + rand * step;
}
