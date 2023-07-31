#include "webserv.hpp"

Server parse_server(std::ifstream& conffile)
{
	std::string key, value, line;
	Server server;

	while (getline(conffile, line))
	{
		if (key == "}")
			break;
		set_key_value(line, key, value);
		if (key == "location")
			parse_location(Server.location);
		if (key == "listen")
			server.set_host_port(value);
		else if (key == "client_max_body_size")
			server.set_body_size(value);
		if (key == "autoindex")
			server.set_autoindex(value);
		else if (key == "root")
			server.set_root(value);
		else if (key == "error_page")
			server.set_error_page(value);
	}
	return server;
}
