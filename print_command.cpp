#include "print_command.h"



print_command::print_command()
{
}


print_command::~print_command()
{
}


void print_command::set_parameters(string line)
{
	vector<string> items;
	boost::algorithm::split(items, line, boost::algorithm::is_space(), boost::algorithm::token_compress_on);
	if (items.size() >= 2) {
		key_ = items[0];
		for (size_t i = 1; i < items.size(); i++) {
			nodes_.push_back(make_shared<node_point>(items[i]));
		}
	}
	else {
		cerr << "Netlist Command .PRINT fail. str = " << line << endl;
		exit(0);
	}
}


string print_command::to_str()
{
	string return_string = ".PRINT";
	for (size_t i = 0; i < nodes_.size(); i++) {
		return_string += "\t" + nodes_[i]->to_str();
	}
	return_string += "\t";
	return return_string;
}