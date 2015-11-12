#pragma once
#include <string>
#include <vector>

using namespace std;

class netlist_context
{
public:
	netlist_context(string header = "");
	~netlist_context();
protected:
	string header_;
	vector<string> contexts_;
};

