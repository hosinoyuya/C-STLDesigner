#include "stl_signal.h"

bool stl_signal::signal_flag_;

stl_signal::stl_signal()
{
}


stl_signal::~stl_signal()
{
}


void stl_signal::set_signal_function()
{
    signal_flag_ = false;
    if (signal(SIGINT, handler)) {
        cerr << "Failed to set signal function." << endl;
        exit(0);
    }
    if (signal(SIGTERM, handler)) {
        cerr << "Failed to set signal function." << endl;
        exit(0);
    }
	/*
	Windwos‚Å“®‚©‚È‚¢‚Ì‚Å‚Ð‚Æ‚Ü‚¸•Û—¯
    if (signal(SIGQUIT, handler)) {
        cerr << "Failed to set signal function." << endl;
        exit(0);
    }
    if (signal(SIGTSTP, handler)) {
        cerr << "Failed to set signal function." << endl;
        exit(0);
    }
	*/
}


void stl_signal::handler(int signal)
{
    signal_flag_ = true;
}
