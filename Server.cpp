#include "Server.hpp"

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
