#ifndef SERVER_HPP
#define SERVER_HPP
#include "Location.hpp"

class Server
{
	short port;
	std::string host;
	int bodySize;
	std::vector<int> statusCode;
	std::string serverName;
	std::string root;
	std::string errorPage;
	std::string autoindex;
	std::vector<Location> location;
	public:
	Server();
	~Server();

	/*getters*/
	std::vector<Location>& get_location();
	std::string& get_serverName();
	std::string& get_host();
	std::string& get_root();
	std::string& get_errorPage();
	std::vector<int>& get_statusCode();
	std::string& get_autoindex();
	short& get_port();
	int& get_bodySize();

	/*setters*/
	void set_host_port(std::string&);
	void set_serverName(std::string&);
	void set_bodySize(std::string&);
	void set_autoindex(std::string&);
	void set_root(std::string&);
	void set_errorPage(std::string&);
	void set_location(std::ifstream&, std::string&);
};

#endif
