#pragma once
#include "simulator.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <regex>
#include <vector>
#include <iostream>
#include <csignal>

using namespace std;

class hspice :
	public simulator
{
public:
	hspice(stl_config config);
	~hspice();
	virtual bool simulate(string file_path);
    static void init_server(stl_config config);
    static void delete_server();
private:
    static int get_port_num(string port_num_file);
    static vector<int> get_ports_;
    static int use_port_index_;
	static bool use_multiserver_;
};

