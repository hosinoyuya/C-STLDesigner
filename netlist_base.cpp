#include "netlist_base.h"
#include <iostream>


netlist_base::netlist_base(string extention, vector<string> spice_extentions, vector<string> spice_extensions_nouse)
{
	extention_ = extention;
	spice_extentions_ = spice_extentions;
	spice_extensions_nouse_ = spice_extensions_nouse;
	title_ = "";
}


netlist_base::~netlist_base()
{
}

void netlist_base::load(string file_path) {
	file_path_ = file_path;
	ifstream ifs(file_path);
	ifs >> title_;

	string line;
	vector<string> lines;
	while (ifs >> line) {
		lines.push_back(line);
	}
	vector<string> content = concat_continue_line(lines);

	for (int i = 0; i < content.size(); i++) {
		cout << content[i];
	}

}

vector<string> netlist_base::concat_continue_line(vector<string> lines)
{
	vector<string> content;

	for (int i = 0; i < lines.size(); i++) {
		if (lines[i][0] == '+') {
			content.push_back(content[content.size()] + lines[i] + "\n");
		}
		else {
			content.push_back(lines[i] + "\n");
		}
	}

	return content;
}
