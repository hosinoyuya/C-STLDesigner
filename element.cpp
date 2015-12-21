#include "element.h"

#include "relement.h"
#include "telement.h"
#include "welement.h"
#include "xelement.h"
#include "nelement.h"

const regex REG_NODE(R"(\w*pt\d*|\d+)");

element::element(string name)
{
	name_ = name;
	length_ = NULL;
	type_ = DEFAULT_ELEMENT;
}


element::~element()
{
}


shared_ptr<element> element::parce(string line)
{
	boost::algorithm::replace_all(line, "$", "");
	vector<string> items;
	boost::algorithm::split(items, line, boost::algorithm::is_space(), boost::algorithm::token_compress_on);

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
	element->separate_parameters(items);

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


void element::set_node(vector<string> &items)
{
	string point;
	for (int i = 0; i < node_num(); i++) {
		if (items.size() > 0) {
			point = items[0];
			items.erase(items.begin());
		}
		else {
			cerr << "invalid node num!" << endl;
			exit(0);
		}
		if (is_node(point)) {
			nodes_.push_back(make_shared<node_point>("", point));
		}
		else {
			cerr << "invalid set_node, pt = " << point << endl;
			exit(0);
		}
	}
}


void element::separate_parameters(vector<string> items)
{
	for (size_t i = 0; i < items.size(); i++) {
		vector<string> separeted_item;
		
		boost::algorithm::split(separeted_item, items[i], boost::is_any_of("="), boost::algorithm::token_compress_on);
		string key;
		string val;
		if (separeted_item.size() >= 2) {
			key = separeted_item[0];
			val = separeted_item[1];
		}
		else {
			key = "";
			val = separeted_item[0];
		}
		set_parameters(key, val);
	}
}


int element::node_num()
{
	return 2;
}


bool element::is_node(string node)
{
	return (regex_match(node, REG_NODE));
}


void element::set_nodes(vector<string> nodes)
{
	nodes_.clear();
	for (size_t i = 0; i < nodes.size(); i++) {
		nodes_.push_back(make_shared<node_point>("", nodes[i]));
	}
}


void element::set_impedance(int impedance)
{
	impedance_ = make_shared<char_impedance>(*impedance_);
	impedance_->value_ = impedance;

}


void element::set_lenght(double length)
{
	length_ = make_shared<line_length>(*length_);
	length_->value_ = length;
}

string element::to_str()
{
	string return_string = name_ + "\t";
	for (size_t i = 0; i < nodes_.size(); i++) {
		return_string += nodes_[i]->to_str() + "\t";
	}
	return_string += get_param_str();
	return return_string;
}