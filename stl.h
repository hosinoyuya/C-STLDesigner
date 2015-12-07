#pragma once
#include "conventional.h"
#include "element.h"
#include "sub_space.h"
#include "stl_line.h"
#include <memory>
#include <list>
#include <vector>

using namespace std;

class stl :
	public conventional
{
public:
	stl(string file_name, stl_config config, shared_ptr<single_score> score = make_shared<single_score>());
	~stl();
	static shared_ptr<single_score> comparison_score_;
	void init_subspace();
	void random_gene_assignment();
	void write_file();
private:
	int index_;
	bool best_flag_;
	vector<shared_ptr<sub_space>> sub_spaces_;
};

