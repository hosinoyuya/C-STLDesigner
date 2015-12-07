#pragma once
#include "netlist_context.h"
#include "command_base.h"
#include "tran_command.h"
#include "ac_command.h"
#include "print_command.h"
#include "model_command.h"
#include "node_param_command.h"
#include "dummy_command.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <regex>

using namespace std;

class netlist_commands :
	public netlist_context
{
public:
	netlist_commands();
	~netlist_commands();
	virtual void parce();
	shared_ptr<tran_command> tran_;
	shared_ptr<ac_command> ac_;
	shared_ptr<print_command> print_;
	shared_ptr<model_command> model_;
	shared_ptr<node_param_command> node_param_;
	shared_ptr<dummy_command> dummy_;
	virtual string to_str();
private:
	vector<shared_ptr<command_base>> commands_;
	vector<string> comments_;
	shared_ptr<command_base> parce_command(string line);
};

