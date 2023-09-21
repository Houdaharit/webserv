#include "Server.hpp"
#include "../webserv.hpp"

Server::Server()
{
	this->port = 0;
	this->bodySize = 0;
	this->serverName = "";
	this->host = "";
	this->root = "";
	this->errorPage = "";
	this->autoindex = "";
}

Server::~Server()
{
//	std::cout << "bye(Server)" << std::endl;
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

short& Server::get_port()
{
	return (this->port);
}

void Server::set_bodySize(std::string& bodySize)
{
	size_t i = 0;
	int m = 0;

	while(i < bodySize.size())
	{
		if (m > 0)
		{
			this->bodySize = -1;
			return ;
		}
		if (!isdigit(bodySize[i]))
		{
			if (bodySize[i] == 'm' || bodySize[i] == 'M')
				m++;
			else
			{
				this->bodySize = -1;
				return ;
			}
		}
		i++;
	}
	this->bodySize = atoi(bodySize.c_str());
}

int& Server::get_bodySize()
{
	return (this->bodySize);
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

void Server::set_errorPage(std::string& error)
{
        size_t pos = 0;
        size_t i = 0;

        while (pos < error.size())
        {
                while (pos < error.size() && error[pos] != ' ' && error[pos] != '\t')
                        pos++;
                std::string tmp = error.substr(i, pos - i);
                if (isNumber(tmp))
                this->statusCode.push_back(atoi(tmp.c_str()));
                else
                        this->errorPage = tmp;
                while (pos < error.size() && (error[pos] == ' ' || error[pos] == '\t'))
                        pos++;
                i = pos;
        }

}

std::vector<int>& Server::get_statusCode()
{
	return (this->statusCode);
}

std::string& Server::get_errorPage()
{
	return (this->errorPage);
}

void Server::set_location(std::ifstream& confile, std::string& path)
{
	this->location.push_back(parse_location(confile, path));
}

std::vector<Location>& Server::get_location()
{
	return (this->location);
}
	
