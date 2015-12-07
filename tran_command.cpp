#include "tran_command.h"


tran_command::tran_command()
{
}


tran_command::~tran_command()
{
}


void tran_command::set_parameters(string line)
{
	vector<string> items;
	boost::algorithm::split(items, line, boost::algorithm::is_space(), boost::algorithm::token_compress_on);
	if (items.size() >= 4) {
		key_ = items[0];
		resolution_ = unit_change::unit_decode(items[1]);
		end_time_ = unit_change::unit_decode(items[2]);
		start_time_ = unit_change::unit_decode(items[3]);
	}
	else {
		cerr << "Netlist Command .TRAN fail. str = " << line << endl;
		exit(0);
	}
}


string tran_command::to_str()
{
	string resolution = unit_change::unit_encode(resolution_);
	string end_time = unit_change::unit_encode(end_time_);
	string start_time = unit_change::unit_encode(start_time_);
	
	return key_ + "\t" + resolution + "\t" + end_time + "\t" + start_time;
}