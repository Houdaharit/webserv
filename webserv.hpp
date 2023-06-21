#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

class Server
{
	std::string server_name;
	std::string host;
	int port;
	int body_size;
	std::string root;
	std::string error_page;
	std::string autoindex;
	public:
		std::string& get_server_name();
		std::string& get_host();
		std::string& get_root();
		std::string& get_error_page();
		std::string& get_autoindex();
		int& get_port();
		int& get_body_size();
		void set_host_port(std::string&);
		void set_server_name(std::string&);
		void set_body_size(std::string&);
		void set_autoindex(std::string&);
};

int check_conf_file(int argc, char** argv);
void trim_front(std::string& str);
void trim_back(std::string& str);
void str_trim(std::string& str);
#endif
