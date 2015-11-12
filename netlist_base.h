#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class netlist_base
{
public:
	netlist_base(string extention, vector<string> spice_extentions, vector<string> spice_extensions_nouse);
	~netlist_base();
	virtual void load(string file_path);
protected:
	string extention_;
	vector<string> spice_extentions_;
	vector<string> spice_extensions_nouse_;
	string title_;
	vector<string> notice_;
	vector<string> contexts_;
private:
	string file_path_;
	vector<string> concat_continue_line(vector<string> lines);
};

