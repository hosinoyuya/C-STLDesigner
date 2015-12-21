#include "stl_timer.h"

clock_t stl_timer::stl_time_;
clock_t stl_timer::stl_start_;
clock_t stl_timer::evaluate_time_;
clock_t stl_timer::evaluate_start_;

stl_timer::stl_timer()
{
}


stl_timer::~stl_timer()
{
}


void stl_timer::init_timer()
{
	stl_time_ = 0;
	evaluate_time_ = 0;
}


void stl_timer::stl_start()
{
	stl_start_ = clock();
}


void stl_timer::stl_stop()
{
	stl_time_ += clock() - stl_start_;
}


void stl_timer::evaluate_start()
{
	evaluate_start_ = clock();
}


void stl_timer::evaluate_stop()
{
	evaluate_time_ += clock() - evaluate_start_;
}


void stl_timer::print_time()
{
	int stl_all_sec = stl_time_ / CLOCKS_PER_SEC;
	int stl_sec = stl_all_sec % 60;
	int stl_mini = stl_all_sec % (60 * 60) / 60;
	int stl_hour = stl_all_sec / (60 * 60);

	int eval_all_sec = evaluate_time_ / CLOCKS_PER_SEC;
	int eval_sec = eval_all_sec % 60;
	int eval_mini = eval_all_sec % (60 * 60) / 60;
	int eval_hour = eval_all_sec / (60 * 60);

	cout << "------------simulation time--------------" << endl;
	cout << "total time : " << stl_hour << "hour" << stl_mini << "min" << stl_sec << "sec" << endl;
	cout << "evaluate time : " << eval_hour << "hour" << eval_mini << "min" << eval_sec << "sec" << endl;
}