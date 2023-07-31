#include "Server.hpp"
#include "webserv.hpp"

Server::Server()
{
	this->port = 0;
	this->body_size = 0;
	this->error = 0;
	this->server_name = "";
	this->host = "";
	this->root = "";
	this->error_page = "";
	this->autoindex = "";
}

Server::~Server()
{
	std::cout << "bye(Server)" << std::endl;
}
void Server::set_host_port(std::string& host_port)
{
	std::size_t pos = host_port.find(':');
	if (pos != std::string::npos)
	{
		this->host = host_port.substr(0, pos);
		this->port = atoi(host_port.substr(pos + 1).c_str());
	}
}

std::string& Server::get_host()
{
	return (this->host);
}

int& Server::get_port()
{
	return (this->port);
}

void Server::set_body_size(std::string& body_size)
{
	size_t i = 0;
	int m = 0;

	while(i < body_size.size())
	{
		if (m > 0)
		{
			this->body_size = -1;
			return ;
		}
		if (!isdigit(body_size[i]))
		{
			if (body_size[i] == 'm' || body_size[i] == 'M')
				m++;
			else
			{
				this->body_size = -1;
				return ;
			}
		}
		i++;
	}
	this->body_size = atoi(body_size.c_str());
}

int& Server::get_body_size()
{
	return (this->body_size);
}

void Server::set_autoindex(std::string& autoindex)
{
	this->autoindex = autoindex;
}

std::string& Server::get_autoindex()
{
	return (this->autoindex);
}

void Server::set_root(std::string& root)
{
	this->root = root;
}

std::string& Server::get_root()
{
	return (this->root);
}

void Server::set_error_page(std::string& error)
{
	size_t pos = 0;

	while (pos < error.size() && error[pos] != ' ' && error[pos] != '\t')
		pos++;
	if (pos < error.size())
	{
		this->error = atoi(error.substr(0, pos).c_str());
		this->error_page = error.substr(pos + 1);
		str_trim(this->error_page);
	}
}

int& Server::get_error()
{
	return (this->error);
}

std::string& Server::get_error_page()
{
	return (this->error_page);
}

void Server::set_location(std::ifstream& confile, std::string& path)
{
	this->location.push_back(parse_location(confile, path));
}

std::vector<Location>& Server::get_location()
{
	return (this->location);
}
	
