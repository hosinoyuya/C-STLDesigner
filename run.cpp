#include <iostream>
#include "stl_main.h"
#include "list_file.h"
#include <time.h>

int main()
{
	stl_main main("config/basic/config_template_W.yml");
	// stl_main main("config/default.yml");
	// stl_main main("config/config_IBIS_10pF_clk_tr200ps_td16102ps_Tran85_Pop100_Bro10.yml");
	main.run();

	//clock_t start = clock();
	//for (int i = 0; i < 100; i++) {
	//	list_file::load_tran_core();
	//}
	//clock_t end = clock();
	//std::cout << "duration = " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "msec.\n";

	return 0;
}