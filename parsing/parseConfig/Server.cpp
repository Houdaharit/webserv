#include "Server.hpp"
#include "../webserv.hpp"

Server::Server()
{
	this->port = 0;
	this->bodySize = 0;
	this->serverName = "";
	this->host = "";
	this->root = "";
	this->autoindex = "OFF";
}
Server::Server(const Server &server)
{
	this->port = server.port;
	this->host = server.host;
	this->bodySize = server.bodySize;
	this->serverName = server.serverName;
	this->root = server.root;
	this->errorPage = server.errorPage;
	this->autoindex = server.autoindex;
	this->location = server.location;
}

Server &Server::operator=(const Server &server)
{
	if (this != &server)
	{
		this->port = server.port;
		this->host = server.host;
		this->bodySize = server.bodySize;
		this->serverName = server.serverName;
		this->root = server.root;
		this->errorPage = server.errorPage;
		this->autoindex = server.autoindex;
		this->location = server.location;
	}
	return (*this);
}

Server::~Server()
{
	//	std::cout << "bye(Server)" << std::endl;
}
void Server::set_host_port(std::string &host_port)
{
	std::size_t pos = host_port.find(':');
	if (pos != std::string::npos)
	{
		this->host = host_port.substr(0, pos);
		this->port = atoi(host_port.substr(pos + 1).c_str());
	}
}

const std::string &Server::get_host() const
{
	return (this->host);
}
const std::string &Server::get_serverName() const
{
	return (this->serverName);
}
const short &Server::get_port() const
{
	return (this->port);
}

void Server::set_serverName(std::string &server_name)
{
	this->serverName = server_name;
}

void Server::set_index(std::string &index)
{
	size_t pos = 0;
	size_t i = 0;

	while (pos < index.size())
	{
		while (pos < index.size() && index[pos] != ' ' && index[pos] != '\t')
			pos++;
		std::string tmp = index.substr(i, pos - i);
		this->index.push_back(tmp);
		while (pos < index.size() && (index[pos] == ' ' || index[pos] == '\t'))
			pos++;
		i = pos;
	}
}

void Server::set_Socket(int fd)
{
	this->socket_fd = fd;
}
int Server::getSocket() const
{
	return (this->socket_fd);
}

void Server::set_bodySize(std::string &bodySize)
{
	size_t pos;

	pos = bodySize.find("M");
	if (pos == std::string::npos)
		pos = bodySize.find("m");
	bodySize = bodySize.substr(0, pos);
	std::istringstream iss(bodySize);

	iss >> this->bodySize;
}

size_t &Server::get_bodySize()
{
	return (this->bodySize);
}

void Server::set_autoindex(std::string &autoindex)
{
	this->autoindex = autoindex;
}

std::string &Server::get_autoindex()
{
	return (this->autoindex);
}

void Server::set_root(std::string &root)
{
	this->root = root;
}

std::string &Server::get_root()
{
	return (this->root);
}

void Server::set_errorPage(std::string &error)
{
	size_t pos = 0;
	size_t i = 0;
	std::vector<std::string> statusCode;
	std::string errorPage;
	std::pair<std::vector<std::string>, std::string> errors;

	while (pos < error.size())
	{
		while (pos < error.size() && error[pos] != ' ' && error[pos] != '\t')
			pos++;
		std::string tmp = error.substr(i, pos - i);
		if (isNumber(tmp))
			statusCode.push_back(tmp);
		else
			errorPage = tmp;
		while (pos < error.size() && (error[pos] == ' ' || error[pos] == '\t'))
			pos++;
		i = pos;
	}
	errors.first = statusCode;
	errors.second = errorPage;
	this->errorPage.push_back(errors);
}

std::vector<std::pair<std::vector<std::string>, std::string> > &Server::get_errorPage()
{
	return (this->errorPage);
}

void Server::set_location(std::ifstream &confile, std::string &path)
{
	this->location.push_back(parse_location(confile, path));
}

std::vector<Location> &Server::get_location()
{
	return (this->location);
}

std::vector<std::string> &Server::get_index()
{
	return (this->index);
}
