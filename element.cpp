#include "element.h"

#include "relement.h"
#include "telement.h"
#include "welement.h"
#include "xelement.h"
#include "nelement.h"

element::element(string name)
{
	name_ = name;
	reg_node_ = R"(\w*pt\d*|\d+)";
}


element::~element()
{
}


shared_ptr<element> element::parce(string line)
{
	string copy_line = boost::algorithm::replace_all_copy(line, "+", " ");
	boost::algorithm::replace_all(copy_line, "$", "");
	vector<string> items;
	boost::algorithm::split(items, copy_line, boost::algorithm::is_space(), boost::algorithm::token_compress_on);

	string name = items[0];
	items.erase(items.begin());
	if (name == "") {
		return NULL;
	}

	shared_ptr<element> element = generate(name);
	if (element == NULL) {
		return NULL;
	}

	element->set_node(items);
	element->set_parameters(items);

	return element;
}

shared_ptr<element> element::generate(string name)
{
	if (name[0] == 'R') {
		return make_shared<relement>(name);
	}
	else if (name[0] == 'T') {
		return make_shared<telement>(name);
	}
	else if (name[0] == 'W') {
		return make_shared<welement>(name);
	}
	else if (name[0] == 'X') {
		return make_shared<xelement>(name);
	}
	else if (name[0] == 'N') {
		return make_shared<nelement>(name);
	}
	else {
		return NULL;
	}
}


void element::set_node(vector<string> items)
{
	for (int i = 0; i < node_num(); i++) {
		string point = items[i];
		if (is_node(point)) {
			nodes_.push_back(make_shared<node_point>("", point));
		}
		else {
			cerr << "invalid set_node, pt = " << point << endl;
		}
	}
}


void element::set_parameters(vector<string> items)
{
	// ŽŸ‰ñ
}


int element::node_num()
{
	return 2;
}


bool element::is_node(string node)
{
	return (regex_match(node, reg_node_));
}
