#include "mgg.h"



mgg::mgg(stl_config config) : normal_ga(config)
{
}


mgg::~mgg()
{
}


void mgg::change(int generation, vector<shared_ptr<stl>>& population)
{
	vector<shared_ptr<stl>> next_population;
	vector<shared_ptr<stl>> offsprings, family;
	shared_ptr<stl> parent1, parent2;

	// 親を２つ選ぶ
	parent1 = extract_random(population);
	parent2 = extract_random(population);

	offsprings = crossover_->crossover(generation, 1, parent1, parent2);

	stl::join_evaluate();
	// 割り込みが発生した場合，または，hspiceが途中で停止した場合
	// 非同期処理が終わった時点でサーバーを停止させexit
	if (stl_signal::signal_flag_ || stl::simulation_failed_flag_) {
		hspice::delete_server();
		exit(0);
	}

	family.insert(family.end(), offsprings.begin(), offsprings.end());
	family.push_back(parent1);
	family.push_back(parent2);

	population.push_back(extract_elete(family));
	population.push_back(extract_random(family));
}


shared_ptr<stl> mgg::extract_elete(vector<shared_ptr<stl>>& population)
{
	double min_value = DBL_MAX;
	int return_position;
	for (size_t i = 0; i < population.size(); i++) {
		if (population[i]->score_->value_ < min_value) {
			min_value = population[i]->score_->value_;
			return_position = i;
		}
	}
	shared_ptr<stl> return_member = population[return_position];
	population.erase(population.begin() + return_position);
	return return_member;
}

shared_ptr<stl> mgg::extract_random(vector<shared_ptr<stl>>& population)
{
	int random_position = stl_random::random_int(0, population.size()-1);
	shared_ptr<stl> return_member = population[random_position];
	population.erase(population.begin() + random_position);
	return return_member;
}