#pragma once
#include "tran_command.h"
#include "stl_config.h"
#include "transient_wave.h"
#include <string>
#include <memory>
#include <map>

using namespace std;

class wave_list_base
{
public:
	wave_list_base(string file_path);
	~wave_list_base();
	virtual void load_tran(shared_ptr<tran_command> tran, stl_config config) = 0;
	map<string, shared_ptr<transient_wave>> waves_;
protected:
	string file_path_;
};