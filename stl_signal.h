#pragma once
#include <csignal>
#include <iostream>

using namespace std;

class stl_signal
{
public:
	stl_signal();
	~stl_signal();
    static void set_signal_function();
    static void handler(int signal);
    static bool signal_flag_;
};
