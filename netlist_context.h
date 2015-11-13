#pragma once
#include <string>
#include <vector>

using namespace std;

class netlist_context
{
public:
	netlist_context(string header = "");
	~netlist_context();
	void operator <<(string line);
protected:
	string header_;
	vector<string> contents_;
};

