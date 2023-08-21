#ifndef REQUEST_HPP
#define REQUEST_HPP
#include "../webserv.hpp"
#include <map>

class Request
{
	std::string httpMethod;
	std::string httpVersion;
	std::string uri;
	std::map<std::string, std::string> requestHeaders;
	public:
	void set_httpMethod(std::string&);
	void set_httpVersion(std::string&);
	void set_uri(std::string&);
	std::string& get_httpMethod();
	std::string& get_httpVersion();
	std::string& get_uri();
	std::map<std::string, std::string>& get_requestHeaders();
};
#endif
