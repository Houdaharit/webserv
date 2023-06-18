#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include <string>
#include <iostream>
#include <fstream>
class config
{
	std::string server_name;
	std::string host;
	int port;
	int body_size;
	std::string root;
	std::string error_page;
	int autoindex;
	public:
		std::string& get_server_name();
		std::string& get_host;
		std::string& get_root;
		std::string& get_error_page();
		int& get_port();
		int& get_body_size();
		int& get_autoindex;
};
#endif
