#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Location.hpp"
#include "Server.hpp"

class Location;
class Server; 

class Parseconf
{
	public:
	std::vector<Server> conf;
};

int check_conf_file(int argc, char** argv);
void trim_front(std::string& str);
void trim_back(std::string& str);
void str_trim(std::string& str);
Server parse_server(std::ifstream&);
Location parse_location(std::ifstream&, std::string&);
void set_key_value(std::string&, std::string&, std::string&);
#endif
