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

int check_conf_file(int argc, char** argv);
void trim_front(std::string& str);
void trim_back(std::string& str);
void str_trim(std::string& str);
void parse_server(Server&, std::string&, std::string&);
void parse_location(Location&, std::string&, std::string&);
#endif
