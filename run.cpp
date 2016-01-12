#include <iostream>
#include "stl_main.h"
#include "list_file.h"
#include <time.h>

int main()
{
	stl_main main1("config/basic/config_template_W_pop8_mu7.yml");
	main1.run();
	stl_main main2("config/basic/config_template_W_pop16_mu7.yml");
	main2.run();
    stl_main main3("config/basic/config_template_W_pop24_mu7.yml");
	main3.run();
    stl_main main4("config/basic/config_template_W_pop32_mu7.yml");
	main4.run();
	//clock_t start = clock();
	//for (int i = 0; i < 100; i++) {
	//	list_file::load_tran_core();
	//}
	//clock_t end = clock();
	//std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "msec.\n";

	return 0;
}
