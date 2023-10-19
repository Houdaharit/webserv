#include "../webserv.hpp"

Server parse_server(std::ifstream &conffile)
{
	std::string key, value, line;
	Server server;

	while (getline(conffile, line))
	{
		set_key_value(line, key, value);
		if (key == "}")
			break;
		if (key == "location")
		{
			if (conffile)
				server.set_location(conffile, value);
		}
		if (key == "server_name")
			server.set_serverName(value);
		if (key == "listen")
			server.set_host_port(value);
		else if (key == "client_max_body_size")
			server.set_bodySize(value);
		if (key == "autoindex")
			server.set_autoindex(value);
		else if (key == "root")
			server.set_root(value);
		else if (key == "error_page")
			server.set_errorPage(value);
	}
	return server;
}
