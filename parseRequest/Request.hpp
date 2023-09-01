#ifndef REQUEST_HPP
#define REQUEST_HPP
#include "../webserv.hpp"
#include <map>

class HttpRequest
{
	std::string httpMethod;
	std::string httpVersion;
	std::string uri;
	std::map<std::string, std::string> headers;
	std::string requestBody;
	public:
	void parse(std::string&);
	HttpRequest();
	~HttpRequest();

	/*setters*/
	void set_request(std::string&);
	void set_httpMethod(std::string&);
	void set_httpVersion(std::string&);
	void set_uri(std::string&);
	void set_headers(std::string&);
	void set_body(std::string&);

	/*getters*/
	std::string& get_httpMethod();
	std::string& get_httpVersion();
	std::string& get_uri();
	std::string& get_body();
	std::map<std::string, std::string>& get_headers();
	
	void is_method(std::string&);
	void printHeaders();
};
#endif
