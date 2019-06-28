#pragma once
#include "conventional.h"
#include "element.h"
#include "sub_space.h"
#include "stl_line.h"
#include "stl_timer.h"
#include "hspice.h"
#include <memory>
#include <list>
#include <vector>
#include <thread>

using namespace std;

class stl :
	public conventional
{
public:
	stl(string file_name, stl_config config, shared_ptr<single_score> score = make_shared<single_score>());
	~stl();
	static shared_ptr<single_score> comparison_score_;
	void init_subspace();
	int cap_interval_change;
	shared_ptr<sub_space> sub;
	vector<double> cap;
	void random_gene_assignment();
	void gene_assignment(vector<shared_ptr<sub_space>> gene);
	void write_file();
	void evaluate();
	void async_evaluate();
	static void join_evaluate();
	vector<shared_ptr<sub_space>> sub_spaces_;
	int index_;
	static bool simulation_failed_flag_;
private:
	bool best_flag_;
	static vector<shared_ptr<thread>> threads_;
};

