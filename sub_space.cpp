#include "sub_space.h"

const regex REG_D(R"(.*(\d))");

sub_space::sub_space(stl_config config)
{
	set_config_parameters(config);
}


sub_space::~sub_space()
{
}


void sub_space::set_config_parameters(stl_config config)
{
	sub_offset_ = config.sub_offset_;
	minimum_impedance_ = config.minimum_inpedance_;
	maximum_impedance_ = config.maximum_inpedance_;
	impedance_step_ = config.impedance_step_;
	minimum_length_ = config.minimum_length_;
	length_step_ = config.length_step_;
}


void sub_space::set_element(shared_ptr<element> elem)
{
	element_ = elem;
	nodes_ = elem->nodes_;

	if (elem->length_ == NULL || elem->length_->key_ == "" || stl_line::length_zero(elem->length_->value_)) {
		cerr << "set length from element failed." << endl;
		exit(0);
	}

	parse_name();
}


void sub_space::parse_name()
{
	vector<string> items;
	boost::algorithm::split(items, element_->name_, boost::is_any_of("_"), boost::algorithm::token_compress_on);
	first_name_ = items[0];
	string stl = items[1];
	segment_num_ = stoi(items[2]);
	smatch match;
	regex_search(items[0], match, REG_D);
	if (match[1].matched == true) {
		index_ = stoi(match[1].str());
	}
	else {
		cerr << "set subspace number or segment num failed." << endl;
		exit(0);
	}
}


void sub_space::split()
{
	double maximum_length = element_->length_->value_;
	vector<double> segment_lengths = get_random_segment_length(minimum_length_, maximum_length, segment_num_);
	vector<int> segment_impedances = get_random_segment_impedance(minimum_impedance_, maximum_impedance_, impedance_step_, segment_num_);
	int point_offset = index_ * sub_offset_;
	for (int i = 0; i < segment_num_; i++) {
		vector<string> points = get_segment_node(i, point_offset);
		shared_ptr<element> segment = get_segment_element(i + 1, points, segment_lengths[i], segment_impedances[i]);
		segments_.push_back(segment);
	}
}


vector<double> sub_space::get_random_segment_length(double min, double max, int segment_num)
{
	double range_min = min;
	double range_max = max - min;
	vector<double> rand_array, segment_length_array;
	
	for (int i = 0; i < segment_num - 1; i++) {
		rand_array.push_back(stl_random::random_double(range_min, range_max));
	}

	sort(rand_array.begin(), rand_array.end());

	rand_array = length_utils::shift_overlap(rand_array, min);
	rand_array = length_utils::shift_overlap_reverse(rand_array, min, range_max);

	segment_length_array = length_utils::get_segment_length_array(rand_array, max);

	double test = fabs(accumulate(segment_length_array.begin(), segment_length_array.end(), 0.0) - max);

	if (segment_length_array.size() != segment_num
		|| *min_element(segment_length_array.begin(), segment_length_array.end()) < min
		|| fabs(accumulate(segment_length_array.begin(), segment_length_array.end(), 0.0) - max) > stl_line::EPSILON) {
		cerr << "random segment length initialization error.\n" << endl;
		exit(0);
	}

	return segment_length_array;
}


vector<int> sub_space::get_random_segment_impedance(int imp_min, int imp_max, int imp_step, int segment_num) {
	vector<int> segment_impedances;
	for (int i = 0; i < segment_num; i++) {
		segment_impedances.push_back(stl_random::frand_between(imp_min, imp_max, imp_step));
	}
	return segment_impedances;
}


vector<string> sub_space::get_segment_node(int index, int point_offset)
{
	// 先頭セグメントの場合
	if (index == 0) {
		return get_segment_node_core(nodes_, 0, point_offset);
	}
	// 終端セグメントの場合
	else if (index == segment_num_ - 1) {
		return get_segment_node_core(nodes_, point_offset + index - 1, 0);
	}
	else {
		return get_segment_node_core(vector<shared_ptr<node_point>>(0), point_offset + index - 1, point_offset + index);
	}
}


vector<string> sub_space::get_segment_node_core(vector<shared_ptr<node_point>> nodes, int input, int output)
{
	vector<string> return_node;
	vector<string> head_half;
	vector<string> tail_half;
	for (size_t i = 0; i < nodes.size() / 2; i++) {
		head_half.push_back(nodes[i]->to_str());
	}
	for (size_t i = nodes.size() / 2; i < nodes.size(); i++) {
		tail_half.push_back(nodes[i]->to_str());
	}
	
	if (input == 0) {
		return_node.insert(return_node.end(), head_half.begin(), head_half.end());
	}
	else {
		return_node.push_back(to_string(input));
		return_node.push_back(to_string(0));
	}

	if (output == 0) {
		return_node.insert(return_node.end(), tail_half.begin(), tail_half.end());
	}
	else {
		return_node.push_back(to_string(output));
		return_node.push_back(to_string(0));
	}
	
	return return_node;
}


shared_ptr<element> sub_space::get_segment_element(int index, vector<string> point, double segment_length, int segment_impedance)
{
	string segment_name;
	segment_name = first_name_ + "_SEG_" + to_string(index);
	switch (element_->type_)
	{
	case T_ELEMENT: {
		shared_ptr<telement> telem = make_shared<telement>(*dynamic_pointer_cast<telement>(element_));
		telem->name_ = segment_name;
		telem->set_impedance(segment_impedance);
		telem->set_lenght(segment_length);
		telem->set_nodes(point);
		return telem;
	}
	case W_ELEMENT: {
		shared_ptr<welement> welem = make_shared<welement>(*dynamic_pointer_cast<welement>(element_));
		welem->name_ = segment_name;
		welem->set_impedance(segment_impedance);
		welem->set_lenght(segment_length);
		welem->set_nodes(point);
		return welem;
	}
	case X_ELEMENT: {
		shared_ptr<xelement> xelem = make_shared<xelement>(*dynamic_pointer_cast<xelement>(element_));
		xelem->name_ = segment_name;
		xelem->set_impedance(segment_impedance);
		xelem->set_lenght(segment_length);
		xelem->set_nodes(point);
		return xelem;
	}
	case N_ELEMENT: {
		shared_ptr<nelement> nelem = make_shared<nelement>(*dynamic_pointer_cast<nelement>(element_));
		nelem->name_ = segment_name;
		nelem->set_impedance(segment_impedance);
		nelem->set_lenght(segment_length);
		nelem->set_nodes(point);
		return nelem;
	}
	default:
		cerr << "invarid element error. " << endl;
		exit(0);
	}
}