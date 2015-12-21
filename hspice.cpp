#include "hspice.h"

const string PORT_NUM_FILE = "port_num.txt";
const regex REG_PORT(R"(^Server is started on .*:(\d+)$)");
vector<int> hspice::get_ports_;
int hspice::use_port_index_;
bool hspice::use_multiserver_;

hspice::hspice(stl_config config) : simulator(config)
{
}


hspice::~hspice()
{
}


void hspice::init_server(stl_config config)
{
    if (config.server_num_ < 1) {
        cerr << "server_num must be one or more." << endl;
    }
	use_multiserver_ = true;
    for (int i = 0; i < config.server_num_; i++) {
        cout << "make server " << to_string(i) << endl;
		int error = run("hspice -CC >& " + PORT_NUM_FILE);
		ifstream ifs(PORT_NUM_FILE);
		// 実行が途中で中断された場合
        if (error != 0 && ifs) {
            delete_server();
            exit(0);
        }
		// 実行が始まる前に終了した場合
		else if (error != 0) {
			use_multiserver_ = false;
			// Windows専用コマンド
			if (run("start hspice -C &") != 0) {
				exit(0);
			}
			return;
		}
		get_ports_.push_back(get_port_num(PORT_NUM_FILE));
    }
    use_port_index_ = 0;
}


void hspice::delete_server()
{
	if (!use_multiserver_) {
		return;
	}
    for (size_t i = 0; i < get_ports_.size(); i++) {
        run("hspice -CC -K -port " + to_string(get_ports_[i]));
    }
}


bool hspice::simulate(string file_path)
{
	string command;
	if (use_multiserver_) {
		command = "hspice -CC " + file_path
			+ " -port " + to_string(get_ports_[use_port_index_]) + " -o " +
			boost::algorithm::replace_all_copy(file_path, config_.netlist_extension_, "");
		if (use_port_index_ < (int)get_ports_.size() - 1) {
			use_port_index_++;
		}
		else {
			use_port_index_ = 0;
		}
	}
	else {
		command = "hspice -C " + file_path + " -o " +
			boost::algorithm::replace_all_copy(file_path, config_.netlist_extension_, "");
	}
    if (run(command) != 0) {
        return false;
    }
    return true;
}


int hspice::get_port_num(string port_num_file)
{
    ifstream ifs(port_num_file);
    string line;
	smatch match;
    while (getline(ifs,line)) {
	    if (regex_search(line, match, REG_PORT)) {
            return stoi(match[1].str());
        }
    }
    return -1;
}
