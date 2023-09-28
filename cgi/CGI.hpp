#ifndef CGI_HPP
#define CGI_HPP
#include "../parsing/webserv"


class HttpRequest;

class Cgi
{
	std::map<std::string, std::string> envVariables;
	HttpRequest request;


	public:
	Cgi();
	~Cgi;

	/*setters*/
	void set_environmentVariables();

	/*getters*/
	std::map<std::string, std::string>& get_envVariables();
};
#endif
