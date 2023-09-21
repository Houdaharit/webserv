#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "parseConfig/Location.hpp"
#include "parseConfig/Server.hpp"

class Location;
class Server; 

class ParseConf
{
	public:
	std::vector<Server> servers;
};

int check_file(int argc, char** argv);
void trim_front(std::string& str);
void trim_back(std::string& str);
void str_trim(std::string& str);
Server parse_server(std::ifstream&);
Location parse_location(std::ifstream&, std::string&);
void set_key_value(std::string&, std::string&, std::string&);
std::vector<std::string> split(std::string&, char);
bool isHexadecimal(std::string&);
void conf_parsing(int, char**);
bool isNumber(std::string&);
#endif
