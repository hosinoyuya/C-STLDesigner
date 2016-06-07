#include "normal_ga.h"



normal_ga::normal_ga(stl_config config)
{
	//crossover_ = make_shared<uniform_crossover>(config);
	crossover_ = make_shared<blx_crossover>(config);
	//crossover_ = make_shared<one_point_crossover>(config);
}


normal_ga::~normal_ga()
{
}


void normal_ga::clear()
{

}


void normal_ga::change(int generation, vector<shared_ptr<stl>>& population)
{
	vector<shared_ptr<stl>> next_population;
	vector<shared_ptr<stl>> offsprings;
	shared_ptr<stl> parent1, parent2;

	// 出来る限りペアを作って交叉する
	for (size_t i = 0; next_population.size() < population.size(); i++) {
		parent1 = get_roulet_member(population);
		parent2 = get_roulet_member(population, parent1);

		offsprings = crossover_->crossover(generation, i, parent1, parent2);

		next_population.insert(next_population.end(), offsprings.begin(), offsprings.end());
	}
    stl::join_evaluate();
    // 割り込みが発生した場合，または，hspiceが途中で停止した場合
    // 非同期処理が終わった時点でサーバーを停止させexit
    if (stl_signal::signal_flag_ || stl::simulation_failed_flag_) {
        hspice::delete_server();
        exit(0);
    }

	population = next_population;
}

shared_ptr<stl> normal_ga::get_roulet_member(vector<shared_ptr<stl>> population, shared_ptr<stl> eliminate_member)
{
	vector<double> roulet_scores;
	double roulet_sum = 0.0;

	for (size_t i = 0; i < population.size(); i++) {
		if (population[i] == eliminate_member) {
			roulet_scores.push_back(0.0);
			continue;
		}
		double score = value_to_score(population[i]->score_->value_);
		roulet_scores.push_back(score);
    }
	double max = *max_element(roulet_scores.begin(), roulet_scores.end());
	double min = *min_element(roulet_scores.begin(), roulet_scores.end(),
		[](const double& left, const double& right)
        {
            // 0.0が最小値にならないようにする
            double left_buf = left == 0.0 ? DBL_MAX : left;
            double right_buf = right == 0.0 ? DBL_MAX : right;
            return left_buf < right_buf;
        });
    // 線形スケーリング
    double score_size = roulet_scores.size();
    double b = (max - min * score_size ) / (score_size - 1);
	for (size_t i = 0; i < roulet_scores.size(); i++) {
		if(roulet_scores[i] != 0.0) roulet_scores[i] += b;
		roulet_sum += roulet_scores[i];
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


double normal_ga::value_to_score(double value)
{
	return pow(1.0 / value, 2);
}