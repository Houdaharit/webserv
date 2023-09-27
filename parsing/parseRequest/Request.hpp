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
	bool chunkedBody;
	std::fstream bodyFile;
	std::string bodyFile_path;
	
	bool isBody;
	size_t requestBodySize;

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
	std::size_t& get_rmaxbodysize();
	std::map<std::string, std::string>& get_headers();
	
	void is_method(std::string&);
	void is_body();
	void printHeaders();
	void unchunkBody(std::string&);
};
#endif
