#include "evaluate_functions.h"


evaluate_functions::evaluate_functions()
{
}

evaluate_functions::~evaluate_functions()
{
}


void evaluate_functions::calc_integral(double time_interval, vector<double> &voltage1, vector<double> &voltage2,
	shared_ptr<point_score> &p_score)
{
	double diff1, diff2;
	double score = 0;
	for (size_t i = 0; i < voltage1.size()-1; i++) {
		diff1 = fabs(voltage2[i] - voltage1[i]);
		diff2 = fabs(voltage2[i+1] - voltage1[i+1]);
		score += (diff1 + diff2) * time_interval / 2.0;
	}
	p_score->set(score);
}


void evaluate_functions::calc_fitting_integral(double time_interval, double shift_ratio,
	vector<double> &voltage1, vector<double> &voltage2, shared_ptr<point_score> &p_score)
{
	double diff1, diff2;
	double score, min_score = numeric_limits<size_t>::max();
	size_t shift_num = voltage1.size() * shift_ratio;
	size_t shift = 0;
	for (size_t i = 0; i < shift_num; i++) {
		score = 0;
		for (size_t j = 0; j < voltage1.size() - 1; j++) {
			diff1 = fabs(voltage2[(j + i) % voltage1.size()] - voltage1[j]);
			diff2 = fabs(voltage2[(j + i + 1) % voltage1.size()] - voltage1[j+1]);
			score += (diff1 + diff2) * time_interval / 2.0;
		}
		if (min_score > score) {
			min_score = score;
			shift = i;
		}
	}

	p_score->set(min_score);
	p_score->shift_ = (double)shift / (double)voltage1.size();
}


void evaluate_functions::caluc_eye_size(double time_interval, double eye_time, double width_margin,
	vector<double> &ideal_voltage, vector<double> &opt_voltage, double eye_height_weight, double eye_width_weight, shared_ptr<point_score> &p_score)
{
	// 1ビット分のデータ数
	int eye_size = eye_time / time_interval;

	// 配列の初期化
	vector<vector<double>> eye_diagram(4);
	vector<double> max_voltage(eye_size, 0);
	for (int i = 0; i < 4; i++) {
		eye_diagram[i].resize(eye_size);
		for (int j = 0; j < eye_size; j++) {
			eye_diagram[i][j] = 0;
		}
	}

	//アイパターンの作成
	for (int i = 0; i < opt_voltage.size() - 1; i++) {
		int eye_pos = i % eye_size;
		if (opt_voltage[i] > 0.0) {
			eye_diagram[0][eye_pos] += opt_voltage[i];
		}
		else {
			eye_diagram[3][eye_pos] += opt_voltage[i];
		}
		if (opt_voltage[i] > max_voltage[eye_pos]) {
			max_voltage[eye_pos] = opt_voltage[i];
		}
	}

	double max_volt = 0.0;
	int eye_start = 0;
	for (int i = 0; i < eye_size; i++) {
		eye_diagram[1][i] = eye_diagram[0][i] - max_voltage[i];
		eye_diagram[2][i] = eye_diagram[3][i] + max_voltage[i];
		// アイパターンの開始地点の決定
		if (max_volt < eye_diagram[1][i]) {
			max_volt = eye_diagram[1][i];
			eye_start = i;
		}
	}

	// アイパターンずらし
	for (int i = 0; i < 4; i++) {
		rotate(eye_diagram[i].begin(), eye_diagram[i].begin() + eye_start, eye_diagram[i].end());
	}

	//アイ開口高さの読み取り
	int start = eye_size * width_margin;
	int end = eye_size * (1 - width_margin);
	int convex_point = -1;
	double min_volt = numeric_limits<double>::min();

	for (int i = start; i < end - 2; i++) {
		// 上に凸
		if (eye_diagram[1][i] < eye_diagram[1][i + 1] && eye_diagram[1][i + 1] > eye_diagram[1][i + 2]
			&& min_volt < eye_diagram[1][i + 1]) {
			min_volt = eye_diagram[1][i + 1];
			convex_point = i + 1;
		}
	}

	if (convex_point == -1) {
		min_volt = numeric_limits<double>::max();
		for (int i = start; i < end; i++) {
			if (min_volt > eye_diagram[1][i]) {
				min_volt = eye_diagram[1][i];
				convex_point = i;
			}
		}
	}

	double eye_height = eye_diagram[2][convex_point] - eye_diagram[1][convex_point];

	//アイ開口幅、ジッタ、面積の読み取り
	int start_point = 0;
	int end_point = 0;
	for (int i = 0; i < eye_size; i++) {
		if (eye_diagram[1][i] < eye_diagram[2][i]) {
			start_point = i;
			break;
		}
	}

	for (int i = start_point; i < eye_size; i++) {
		if (eye_diagram[1][i] > eye_diagram[2][i]) {
			end_point = i;
			break;
		}
	}

	double eye_width = (end_point - start_point) * time_interval;

	if (eye_height < 0) eye_height = 0;
	p_score->set(1.0 / ((eye_width / eye_time)*eye_width_weight + eye_height*eye_height_weight));
	p_score->set_eye_info(eye_diagram, eye_width, eye_height);		
}