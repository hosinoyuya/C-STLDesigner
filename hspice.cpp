#include "hspice.h"

const string PORT_NUM_FILE = "port_num.txt";
const regex REG_PORT(R"(^Server is started on .*:(\d+)$)");
vector<int> hspice::get_ports_;
int hspice::use_port_index_;

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
    for (int i = 0; i < config.server_num_; i++) {
        cout << "make server " << to_string(i) << endl;
        if (run("hspice -CC >& " + PORT_NUM_FILE) != 0) {
            delete_server();
            exit(0);
        }
        get_ports_.push_back(get_port_num(PORT_NUM_FILE));
    }
    use_port_index_ = 0;
}


void hspice::delete_server()
{
    for (size_t i = 0; i < get_ports_.size(); i++) {
        run("hspice -CC -K -port " + to_string(get_ports_[i]));
    }
}


bool hspice::simulate(string file_path)
{
	string command = "hspice -CC " + file_path
        + " -port " + to_string(get_ports_[use_port_index_]) + " -o " + 
		boost::algorithm::replace_all_copy(file_path, config_.netlist_extension_, "");
    if (use_port_index_ < get_ports_.size()-1) {
        use_port_index_++;
    }
    else {
        use_port_index_ = 0;
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
