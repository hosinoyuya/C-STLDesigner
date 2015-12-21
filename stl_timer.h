#pragma once
#include <time.h>
#include <iostream>

using namespace std;

class stl_timer
{
public:
	stl_timer();
	~stl_timer();
	static void init_timer();
	static void stl_start();
	static void stl_stop();
	static void evaluate_start();
	static void evaluate_stop();
	static void print_time();
private:
	static clock_t stl_time_;
	static clock_t stl_start_;
	static clock_t evaluate_time_;
	static clock_t evaluate_start_;
};

