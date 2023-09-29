#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "parseConfig/Location.hpp"
#include "parseConfig/Server.hpp"
#include "parseRequest/Request.hpp"

class Location;
class Server; 
class HttpRequest;

class ParseConf
{
	public:
		std::vector<Server> servers;
		void parsing(int, char**);
		void read_file(std::ifstream&);
		std::vector<Server>& get_servers();
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
bool isNumber(std::string&);
#endif
