#include "dummy_command.h"

#include <iostream>

dummy_command::dummy_command()
{
}


dummy_command::~dummy_command()
{
}


void dummy_command::set_parameters(string line)
{
	line_ = line;
}


string dummy_command::to_str()
{
	return line_;
}