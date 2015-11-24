#include "netlist_commands.h"

const regex REG_TRAN(R"(\.TRAN.*)", regex_constants::icase);
const regex REG_AC(R"(\.AC.*)", regex_constants::icase);
const regex REG_PRINT(R"(\.PRINT.*)", regex_constants::icase);
const regex REG_MODEL(R"(\.MODEL.*)", regex_constants::icase);
const regex REG_NODE(R"(\.node_param.*)", regex_constants::icase);
const regex REG_INCLUDE(R"(\.INCLUDE.*)", regex_constants::icase);
const regex REG_DUMMY(R"(\.\w+.*)", regex_constants::icase);

netlist_commands::netlist_commands()
{
	header_ = "*** Netlist Commands *** -------------------------------------------------------------*\n";
	tran_ = NULL;
	ac_ = NULL;
	print_ = NULL;
	model_ = NULL;
	node_param_ = NULL;
	dummy_ = NULL;
}


netlist_commands::~netlist_commands()
{
}


void netlist_commands::parce()
{
	for (size_t i = 0; i < context_.size(); i++) {
		if (context_[i][0] != '*') {
			commands_.push_back(parce_command(context_[i]));
			comments_.push_back("");
		}
		else {
			comments_.push_back(context_[i]);
		}
	}
}


shared_ptr<command_base> netlist_commands::parce_command(string line)
{
	if (regex_match(line, REG_TRAN)) {
		tran_ = make_shared<tran_command>();
		tran_->set_parameters(line);
		return tran_;
	}
	if (regex_match(line, REG_AC)) {
		ac_ = make_shared<ac_command>();
		ac_->set_parameters(line);
		return ac_;
	}
	if (regex_match(line, REG_PRINT)) {
		print_ = make_shared<print_command>();
		print_->set_parameters(line);
		return print_;
	}
	if (regex_match(line, REG_MODEL)) {
		model_ = make_shared<model_command>();
		model_->set_parameters(line);
		return model_;
	}
	if (regex_match(line, REG_NODE)) {
		node_param_ = make_shared<node_param_command>();
		node_param_->set_parameters(line);
		return node_param_;
	}
	// if (regex_match(line, REG_INCLUDE) || regex_match(line, REG_DUMMY)) {
	//	dummy_ = make_shared<dummy_command>(line);
	//	return dummy_;
	//}
	dummy_ = make_shared<dummy_command>();
	dummy_->set_parameters(line);
	return dummy_;
}