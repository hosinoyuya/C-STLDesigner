#pragma once
#include "element.h"
#include "line_length.h"
#include <string>
#include <memory>

using namespace std;

class line_element_base :
	public element
{
public:
	line_element_base(string name);
	~line_element_base();
private:
	virtual int node_num();
	virtual void set_parameters(string key, string val);
	virtual void set_spetialized_parameters(string key, string val);
	shared_ptr<line_length> length_;
};
