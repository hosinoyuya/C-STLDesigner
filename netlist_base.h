#pragma once
#include "netlist_context.h"
#include "stl_circuit.h"
#include "netlist_circuit.h"
#include "netlist_commands.h"
#include "netlist_scores.h"
#include "single_score.h"
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <memory>
#include <fstream>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

class netlist_base
{
public:
	netlist_base(string extention, vector<string> spice_extentions, vector<string> spice_extensions_nouse);
	~netlist_base();
	virtual void load(string file_path);
	shared_ptr<netlist_context> notice_;
	shared_ptr<stl_circuit> stl_circuit_;
	shared_ptr<netlist_circuit> versus_circuit_;
	shared_ptr<netlist_circuit> trigger_circuit_;
	shared_ptr<netlist_commands> commands_;
	shared_ptr<netlist_scores> scores_;
	string file_path_;
	void write(string file_path = "");
	string to_str();
	void write_score(shared_ptr<single_score> score);
protected:
	string extention_;
	vector<string> spice_extentions_;
	vector<string> spice_extensions_nouse_;
	string title_;
	vector<shared_ptr<netlist_context>> contexts_;
private:
	vector<string> concat_continue_line(vector<string> lines);
	shared_ptr<netlist_context> set_context(string line);
	void parce_contexts();
};