#pragma once
#include "wave_list_base.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <regex>
#include <stdlib.h>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

class lis_file :
	public wave_list_base
{
public:
	lis_file(string file_path);
	~lis_file();
	virtual void load_tran(shared_ptr<tran_command> tran);
private:
	bool is_error(vector<string> &lis_data);
	int get_data_num(shared_ptr<tran_command> tran);
	void remove_intoro(vector<string> &lis_data);
	void set_data_map(vector<string> &lis_data, int data_num, map<string, vector<string>> &data_map_loop, vector<string> &labels_loop);
};

