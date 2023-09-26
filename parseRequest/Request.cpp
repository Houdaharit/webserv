#include "Request.hpp"

HttpRequest::HttpRequest() : httpMethod(""),
	httpVersion(""),
	uri(""), 
	requestBody(""), 
	chunkedBody(false),
	isBody(false),
		     requestBodySize(0)
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

void HttpRequest::is_body()
{
	std::map<std::string, std::string>::iterator it_length = this->headers.find("Content-Length");
	std::map<std::string, std::string>::iterator it_chunk = this->headers.find("Transfer-Encoding");
	if (it_length != this->headers.end() || it_chunk != this->headers.end())
		this->isBody = true;
	if (it_chunk != this->headers.end())
		this->chunkedBody = true;
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
	//check version
	this->httpVersion = version;
}

void HttpRequest::set_request(std::string& request_line)
{
	std::vector<std::string> request = split(request_line, ' ');
	if (request.size() != 3)
		std::cout << "Throw Exception" << std::endl;
	set_httpMethod(request[0]);
	set_uri(request[1]);
	set_httpVersion(request[2]);

}

void HttpRequest::printHeaders()
{
	std::map<std::string, std::string>::iterator it;

	for(it = this->headers.begin(); it!= this->headers.end(); ++it)
		std::cout << it->first << ":" << it->second << std::endl;
}



void HttpRequest::set_headers(std::string& headers)
{
	std::string CRLF("\r\n");
	size_t crlf_pos, delim_pos;;
	std::string key, value;
	std::string header_line;

	while(headers.find(CRLF) != std::string::npos)
	{
		crlf_pos = headers.find(CRLF);
		header_line = headers.substr(0, crlf_pos);
		headers = headers.substr(crlf_pos + 2);
		if (header_line.empty())
			break;
		delim_pos = header_line.find(":");
		if (delim_pos != std::string::npos)
		{
			key = header_line.substr(0, delim_pos);
			value = header_line.substr(delim_pos + 1);
			trim_front(value);
			this->headers.insert(std::pair<std::string, std::string>(key, value));
		}
		//unfold multiple-line header field
	}
	//	printHeaders();
}

void HttpRequest::unchunkBody(std::string& body)
{
	std::string chunk;
	std::string CRLF("\r\n");
	size_t crlf_pos;

	while(1)
	{
		crlf_pos = body.find(CRLF);
		if (crlf_pos == 0)
			break;
		chunk = body.substr(0, crlf_pos);
		body = body.substr(crlf_pos + 2);
		if (chunk == "0")
			break;
		else if (isHexadecimal(chunk))
			continue;
		this->requestBody = this->requestBody + chunk;
		this->requestBodySize += chunk.size();
	}
	std::cout << this->requestBody << std::endl;
}

void HttpRequest::set_body(std::string& body)
{
	(void)body;	
	std::string chunk;
	if (this->chunkedBody)
		unchunkBody(body);
	else
	{
		this->requestBody = body;
		std::map<std::string, std::string>::iterator it_chunk = this->headers.find("Transfer-Encoding");
		this->requestBodySize = atoi(it_chunk->second.c_str()); 
	}
}

void HttpRequest::parse(std::string& read_request)
{
	std::string CRLF("\r\n");
	std::string request_line;
	std::string headers_lines;
	std::string rest;
	size_t pos;

	pos = read_request.find(CRLF);
	if (pos != std::string::npos)
	{	
		request_line = read_request.substr(0, pos);
		headers_lines = read_request.substr(pos + 2);
		set_request(request_line);
		set_headers(headers_lines);
		rest = headers_lines;

		is_body();
		if (this->isBody)
			set_body(rest);
		/*else if (this->httpMethod == "POST" || this->httpMethod == "PUT")
		  std::cout << "Throw exception Content-Length" << std::endl;*/
	}
	//think about throwing exception weird request
}

std::string& HttpRequest::get_httpMethod()
{
	return (this->httpMethod);
}

std::string& HttpRequest::get_httpVersion()
{
	return (this->httpVersion);
}

std::string& HttpRequest::get_uri()
{
	return (this->uri);
}

std::string& HttpRequest::get_body()
{
	return (this->requestBody);
}

std::map<std::string, std::string>& HttpRequest::get_headers()
{
	return (this->headers);
}

std::size_t&  HttpRequest::get_rmaxbodysize()
{
	return (this->requestBodySize);
}