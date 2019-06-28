#pragma once
#include <random>
#include <iostream>

using namespace std;

class stl_random
{
public:
	stl_random();
	~stl_random();
	static void srand(unsigned int seed);
	static int random_int(int min, int max);
	static double random_double(double min, double max);
	static int frand_between(int min, int max, int step);
	static double frand_between_double(double min, double max, double step);
private:
	static mt19937 mt;
};

