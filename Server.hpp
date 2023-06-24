#ifndef SERVER_HPP
#define SERVER_HPP
#include "Location.hpp"

class Location;

class Server
{
    int port;
    int body_size;
    int error;
    std::string server_name;
    std::string host;
    std::string root;
    std::string error_page;
    std::string autoindex;
    Location location;
    public:
        std::string& get_server_name();
        std::string& get_host();
        std::string& get_root();
        std::string& get_error_page();
		int& get_error();
        std::string& get_autoindex();
        int& get_port();
        int& get_body_size();
        void set_host_port(std::string&);
        void set_server_name(std::string&);
        void set_body_size(std::string&);
        void set_autoindex(std::string&);
		void set_root(std::string&);
		void set_error_page(std::string&);
};

#endif
