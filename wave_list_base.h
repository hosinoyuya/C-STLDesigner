#pragma once
#include "tran_command.h"
#include <string>
#include <memory>

using namespace std;

class wave_list_base
{
public:
	wave_list_base(string file_path);
	~wave_list_base();
	virtual void load_tran(shared_ptr<tran_command> tran) = 0;
protected:
	string file_path_;
};