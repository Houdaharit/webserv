#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <iostream>
#include <vector>
#include "webserv.hpp"

class Location
{
	std::string path;
	std::string root;
	std::string index;
	std::string try_file;
	int error;
	std::string redirection;
	int redirect;
	std::vector<std::string> allow_methods;
	std::string fastcgi_pass;
	std::string error_page;
	/*std::string proxy_pass;
	  std::string proxy_redirect;
	  std::string proxy_set_header;
	  std::string proxy_cache;*/
	//std::string limit_except;
	public:
	Location();
	~Location();
	void set_error_page(std::string&);
	void set_index(std::string&);
	void set_methods(std::string&);
	void set_redirection(std::string&);
	void set_root(std::string&);
	void set_path(std::string&);
	std::string& get_index();
	std::vector<std::string>& get_methods();
	std::string& get_redirection();
	std::string& get_root();
	std::string& get_error_page();
	std::string& get_path();
	int& get_error();
	int& get_redirect();

};

#endif
