#include "stl_timer.h"

time_t stl_timer::stl_start_;
time_t stl_timer::stl_end_;
clock_t stl_timer::evaluate_start_;
clock_t stl_timer::evaluate_end_;
clock_t stl_timer::evaluate_clock_;
time_t stl_timer::evaluate_time_;

stl_timer::stl_timer()
{
}


stl_timer::~stl_timer()
{
}


void stl_timer::init_timer()
{
	evaluate_clock_ = 0;
	evaluate_time_ = 0;
}


void stl_timer::stl_start()
{
	time(&stl_start_);
}


void stl_timer::stl_stop()
{
	time(&stl_end_);
}


void stl_timer::evaluate_start()
{
	evaluate_start_ = clock();
}


void stl_timer::evaluate_stop()
{
	evaluate_end_ = clock();
    clock_t clock_diff = evaluate_end_ - evaluate_start_ + evaluate_clock_;
    // 1秒以下の値を保存
    evaluate_clock_ = clock_diff % CLOCKS_PER_SEC;
    evaluate_time_ += clock_diff / CLOCKS_PER_SEC;
}


void stl_timer::print_time()
{
	int stl_all_sec = difftime(stl_end_, stl_start_);
	int stl_sec = stl_all_sec % 60;
	int stl_mini = stl_all_sec % (60 * 60) / 60;
	int stl_hour = stl_all_sec / (60 * 60);

	int eval_all_sec = evaluate_time_;
	int eval_sec = eval_all_sec % 60;
	int eval_mini = eval_all_sec % (60 * 60) / 60;
	int eval_hour = eval_all_sec / (60 * 60);

	cout << "------------simulation time--------------" << endl;
	cout << "total time : " << stl_hour << "hour" << stl_mini << "min" << stl_sec << "sec" << endl;
	cout << "evaluate time : " << eval_hour << "hour" << eval_mini << "min" << eval_sec << "sec" << endl;
}
