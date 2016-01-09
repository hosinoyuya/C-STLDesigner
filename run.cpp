#include <iostream>
#include "stl_main.h"
#include "list_file.h"
#include <time.h>

int main()
{
	stl_main main0("config/basic/config_template_W_pop12_mu5.yml");
	main0.run();
	stl_main main1("config/basic/config_template_W_pop20_mu5.yml");
	main1.run();
	//stl_main main4("config/basic/config_template_W_pop40_mu5.yml");
	//main4.run();
	//clock_t start = clock();
	//for (int i = 0; i < 100; i++) {
	//	list_file::load_tran_core();
	//}
	//clock_t end = clock();
	//std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "msec.\n";

	return 0;
}
