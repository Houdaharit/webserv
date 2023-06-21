#include "webserv.hpp"

void Server::set_host(std::string host)
{
	this->host = host;
}

void Server::set_port(std::string port)
{
	this->port = atoi(port.c_str());
}

std::string& Server::get_host()
{
	return (this->host);
}

int& Server::get_port()
{
	return (this->port);
}
