#include <iostream>
#include "stl_main.h"
#include "list_file.h"
#include <time.h>

int main()
{
	// 設定ファイルを指定し、プログラムを実行
	stl_main main("config/basic/config_template_T.yml");
	main.run();

	return 0;
}
