#include "Cgi.hpp"

Cgi::Cgi()
{
}

Cgi::~Cgi()
{
}


void Cgi::set_environmentVariables()
{
	std::map<std::string, std::string> headers = this->request.get_headers();

	this->envVariables["CONTENT_LENGTH"] = request.get_bodySize();
	this->envVariables["CONTENT_TYPE"] = headers["CONTENT_TYPE"]; 
	this->envVariables["REMOTE_IDENT"] = "";
	//this->envVariables["REMOTE_USER"] = "";
	this->envVariables["AUTH_TYPE"] =  "";
	this->envVariables["REMOTE_ADDR"] = "";
	this->envVariables["REMOTE_HOST"] = 
	this->envVariables["QUERY_STRING"] = 
	//this->envVariables["SCRIPT_NAME"] = this->request.get_stringQuery(); 
	this->envVariables["PATH_TRANSLATED"] = 
	this->envVariables["PATH_INFO"] = 
	this->envVariables["REQUEST_METHOD"] = this->request.get_httpMethod();
	this->envVariables["SERVER_PROTOCOL"] = "HTTP/1.1" 
	this->envVariables["SERVER_PORT"] = this->server.get_port(); 
}
