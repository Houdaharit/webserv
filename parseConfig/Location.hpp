#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <iostream>
#include <vector>
#include "../webserv.hpp"

class Location
{
	std::string path;
	std::string root;
	std::string index; //change it to a vector
	std::string try_file;
	std::vector<int> statusCode; //I need to change it to a vector
	std::string redirection;
	int redirect;
	std::vector<std::string> methods;
	std::string fastcgi_pass;
	std::string errorPage;
	std::string upload;
	public:
	Location();
	~Location();

	/*setters*/
	void set_errorPage(std::string&);
	void set_index(std::string&);
	void set_methods(std::string&);
	void set_redirection(std::string&);
	void set_root(std::string&);
	void set_path(std::string&);
	void set_upload(std::string&);

	/*getters*/
	std::string& get_index();
	std::vector<std::string>& get_methods();
	std::string& get_redirection();
	std::string& get_root();
	std::string& get_errorPage();
	std::string& get_path();
	std::string& get_upload();
	std::vector<int>& get_statusCode();
	int& get_redirect();
};

#endif
