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
	virtual void parce();
	virtual string to_str();
protected:
	string header_;
	vector<string> context_;
	vector<string> contents_;
};
