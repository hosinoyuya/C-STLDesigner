#include "normal_ga.h"



normal_ga::normal_ga(stl_config config)
{
	crossover_ = make_shared<uniform_crossover>(config);
}


normal_ga::~normal_ga()
{
}


void normal_ga::clear()
{

}


void normal_ga::change(int generation, vector<shared_ptr<stl>>& population)
{
	cout << "generation : " << generation << endl;

	vector<shared_ptr<stl>> next_population;
	vector<shared_ptr<stl>> offsprings;
	shared_ptr<stl> parent1, parent2;

	// 出来る限りペアを作って交叉する
	for (size_t i = 0; i < population.size() / 2; i++) {
		parent1 = get_roulet_member(population);
		parent2 = get_roulet_member(population, parent1);

		offsprings = crossover_->crossover(generation, i, parent1, parent2);

		next_population.insert(next_population.end(), offsprings.begin(), offsprings.end());
	}

	population = next_population;
}

shared_ptr<stl> normal_ga::get_roulet_member(vector<shared_ptr<stl>> population, shared_ptr<stl> eliminate_member)
{
	vector<double> roulet_scores;
	double roulet_sum = 0.0;
	// 誤差面積が少ない方が優秀なので誤差面積の逆数をスコアにする
	for (size_t i = 0; i < population.size(); i++) {
		if (population[i] == eliminate_member) {
			roulet_scores.push_back(0.0);
			continue;
		}
		double score = 1.0 / population[i]->score_->value_;
		roulet_scores.push_back(score);
		roulet_sum += score;
	}

	double random_position = stl_random::random_double(0.0, roulet_sum);

	double roulet_position = 0.0;
	for (size_t i = 0; i < roulet_scores.size(); i++) {
		if (population[i] == eliminate_member) continue;
		roulet_position += roulet_scores[i];
		if (roulet_position > random_position) {
			return population[i];
		}
	}

	return population[0];
}