#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <iostream>

class Location
{
    std::string root;
    std::string index;
    std::string try_file;
    int error;
    std::string return_;
    //std::string limit_except;
	std::string allow_methods;
    std::string fastcgi_pass;
    std::string error_page;
    /*std::string proxy_pass;
    std::string proxy_redirect;
    std::string proxy_set_header;
    std::string proxy_cache;*/
	public:
	int get_error();
};

#endif
