#include "Request.hpp"

HttpRequest::HttpRequest(): httpMethod(""), httpVersion(""), uri("")
{

}

HttpRequest::~HttpRequest()
{
}

void HttpRequest::is_method(std::string& method)
{
	std::vector<std::string> methods;
	methods.push_back("GET");
	methods.push_back("POST");
	methods.push_back("DELETE");
	methods.push_back("PUT");
	for(size_t i = 0; i < methods.size(); i++)
	{
		if (method == methods[i])
			return ;
	}
	//throw exception
	std::cout << "Method exception" << std::endl;
}

void HttpRequest::set_httpMethod(std::string& method)
{
	is_method(method);
	this->httpMethod = method;
}

void HttpRequest::set_uri(std::string& uri)
{
	//check if uri
	this->uri = uri;
}	

void HttpRequest::set_httpVersion(std::string& version)
{
	this->httpVersion = version;
}

void HttpRequest::set_request(std::string& request_line)
{
	std::vector<std::string> request = split(request_line, ' ');
	if (request.size() != 3)
		std::cout << "Throw Exception" << std::endl;
	/*define them*/
	
	   set_httpMethod(request[0]);
	   set_uri(request[1]);
	   set_httpVersion(request[2]);
	   
}

void HttpRequest::parse(std::string& read_request)
{
	std::string CRLF("\r\n");
	std::string request_line;
	std::string headers_lines;
	size_t pos;

	pos = read_request.find(CRLF);
	if (pos != std::string::npos)
	{
		request_line = read_request.substr(0, pos);
		headers_lines = read_request.substr(pos + 2);
		set_request(request_line);
	//	set_headers(headers_lines);
	}

}
