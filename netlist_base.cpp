#include "netlist_base.h"
#include <iostream>


netlist_base::netlist_base(string extention, vector<string> spice_extentions, vector<string> spice_extensions_nouse)
{
	extention_ = extention;
	spice_extentions_ = spice_extentions;
	spice_extensions_nouse_ = spice_extensions_nouse;
	title_ = "";
	reg_context_marker_ = R"(\*\*\*(.*)\*\*\* -+\*)";
	reg_context_end_ = R"(\*-+\*)";
}


netlist_base::~netlist_base()
{
}

void netlist_base::load(string file_path) {
	file_path_ = file_path;
	ifstream ifs(file_path);
	ifs >> title_;
	//cout << file_path << endl;

	string line;
	vector<string> lines;
	while (getline(ifs, line)) {
		lines.push_back(line);
	}
	vector<string> content = concat_continue_line(lines);

	regex  reg_exp;
	shared_ptr<netlist_context> context = NULL;
	for (size_t i = 0; i < content.size(); i++) {
		if (regex_match(content[i], reg_context_end_)) {
			if (context != NULL) {
				contexts_.push_back(context);
			}
			context = NULL;
		}
		if (regex_match(content[i], reg_context_marker_)) {
			context = set_context(content[i]);
		}

		if (context != NULL) {
			*context << content[i];
		}
	}

	parce_contexts();
}

vector<string> netlist_base::concat_continue_line(vector<string> lines)
{
	vector<string> content;

	for (size_t i = 0; i < lines.size(); i++) {
		if (lines[i][0] == '+') {
			content.push_back(content[content.size()] + lines[i]);
		}
		else {
			content.push_back(lines[i]);
		}
	}

	return content;
}


shared_ptr<netlist_context> netlist_base::set_context(string line)
{
	if (line.find("Notice") != string::npos) {
		notice_ =  make_shared<netlist_context>(line);
		return notice_;
	}
	if (line.find("STL") != string::npos) {
		stl_circuit_ = make_shared<stl_circuit>(line);
		return stl_circuit_;
	}
	if (line.find("Versus") != string::npos) {
		versus_circuit_ = make_shared<netlist_circuit>(line);
		return versus_circuit_;
	}
	if (line.find("Trigger") != string::npos) {
		trigger_circuit_ = make_shared<netlist_circuit>(line);
		return trigger_circuit_;
	}
	if (line.find("Commands") != string::npos) {
		commands_ = make_shared<netlist_commands>();
		return commands_;
	}
	if (line.find("Scores") != string::npos) {
		scores_ = make_shared<netlist_scores>();
		return scores_;
	}
	return NULL;
}


void netlist_base::parce_contexts()
{
	if (stl_circuit_ != NULL) {
		stl_circuit_->parce();
	}
	if (versus_circuit_ != NULL) {
		versus_circuit_->parce();
	}
	if (trigger_circuit_ != NULL) {
		trigger_circuit_->parce();
	}
	if (commands_ != NULL) {
		commands_->parce();
	}
	if (scores_ != NULL) {
		scores_->parce();
	}
}