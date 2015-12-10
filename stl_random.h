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
	static int random_int(int max, int min);
	static double random_double(double max, double min);
	static int frand_between(int min, int max, int step);
private:
	static mt19937 mt;
};

