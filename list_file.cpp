#include "list_file.h"



list_file::list_file()
{
}


list_file::~list_file()
{
}


void list_file::load_tran_core()
{
	ifstream ifs("config/default.lis");
	if (ifs.fail())
	{
		cerr << "lis�t�@�C���̓ǂݍ��݂Ɏ��s" << std::endl;
	}

	map <string, vector<string>> list_data;
	vector<string> labels;

	string line;
	while (getline(ifs, line)) {
		if (line.find("transient analysis") != string::npos) {
			break;
		}
	}
    // 4�s�ǂݔ�΂�
	for (int i = 0; i < 4; i++) {
		if (!getline(ifs, line)) break;
	}
	istringstream iss(line);
	string lavel;
	// ���x���̎擾
	labels.push_back("time");
	do {
		iss >> skipws;
		iss >> lavel;
		labels.push_back(lavel);
	} while (iss);

	// �l�̓ǂݍ���
	while (getline(ifs, line)) {
		if (line.find("y") != string::npos) break;
		istringstream iss(line);
		string val;
		int line_count = 0;
		do {
			iss >> skipws;
			iss >> val;
			list_data[labels[line_count]].push_back(val);
			line_count++;
		} while (iss);
	}
}
