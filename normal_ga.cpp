#include "normal_ga.h"



normal_ga::normal_ga(stl_config config)
{
	//crossover_ = make_shared<uniform_crossover>(config);
	crossover_ = make_shared<blx_crossover>(config);
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

	// �o�������y�A������Č�������
	for (size_t i = 0; next_population.size() < population.size(); i++) {
		parent1 = get_roulet_member(population);
		parent2 = get_roulet_member(population, parent1);

		offsprings = crossover_->crossover(generation, i, parent1, parent2);

		next_population.insert(next_population.end(), offsprings.begin(), offsprings.end());
	}
    stl::join_evaluate();
    // ���荞�݂����������ꍇ�C�܂��́Chspice���r���Œ�~�����ꍇ
    // �񓯊��������I��������_�ŃT�[�o�[���~����exit
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
	shared_ptr<stl> max = *max_element(population.begin(), population.end(),
		[](const shared_ptr<stl>& left, const shared_ptr<stl>& right) {return left->score_->value_ < right->score_->value_; });
	// double max_score = max->score_->value_;
	// �덷�ʐς����Ȃ������D�G�Ȃ̂Ō덷�ʐς̋t�����X�R�A�ɂ���
	for (size_t i = 0; i < population.size(); i++) {
		if (population[i] == eliminate_member) {
			roulet_scores.push_back(0.0);
			continue;
		}
		double score = pow(1.0 / population[i]->score_->value_, 2);
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
