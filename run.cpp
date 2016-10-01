#include <iostream>
#include "stl_main.h"
#include "list_file.h"
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
	// 設定ファイルを指定し、プログラムを実行
	if (argc == 2) {
		//stl_main main("config/basic/config_template_W_akt_isolation_fitting.yml");
		stl_main main(argv[1]);
		main.run();
	} else {
		cout << "設定ファイルを引数として1つ指定してください。" << endl;
	}

	return 0;
}
