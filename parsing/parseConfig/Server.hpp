#ifndef SERVER_HPP
#define SERVER_HPP
#include "Location.hpp"

class Server
{
	short port;
	std::string host;
	int bodySize;
	std::string serverName;
	std::string root;
	std::vector<std::pair<std::vector<std::string>, std::string> > errorPage;
	std::string autoindex;
	std::vector<Location> location;
	std::vector<std::string> index;
	public:
	Server();
	~Server();

	/*getters*/
	std::vector<std::string>& get_index();
	std::vector<Location>& get_location();
	std::string& get_serverName();
	std::string& get_host();
	std::string& get_root();
	std::vector<std::pair<std::vector<std::string>, std::string> >& get_errorPage();
	std::string& get_autoindex();
	short& get_port();
	int& get_bodySize();

	/*setters*/
	void set_index(std::string&);
	void set_host_port(std::string&);
	void set_serverName(std::string&);
	void set_bodySize(std::string&);
	void set_autoindex(std::string&);
	void set_root(std::string&);
	void set_errorPage(std::string&);
	void set_location(std::ifstream&, std::string&);
};

#endif
