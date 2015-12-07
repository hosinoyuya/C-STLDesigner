#include "node_param_command.h"



node_param_command::node_param_command()
{
}


node_param_command::~node_param_command()
{
}


void node_param_command::set_parameters(string line)
{
	line_ = line;
}


string node_param_command::to_str()
{
	return line_;
}