#include "ac_command.h"



ac_command::ac_command()
{
}


ac_command::~ac_command()
{
}


void ac_command::set_parameters(string line)
{
	line_ = line;
}


string ac_command::to_str()
{
	return line_;
}