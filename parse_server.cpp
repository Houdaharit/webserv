#include "webserv.hpp"

Server parse_server(std::ifstream& conffile)
{
	std::string key, value, line;
	Server server;
	int i = 0;

	while (getline(conffile, line))
	{
		set_key_value(line, key, value);
		if (key == "}")
			break;
		if (key == "location")
		{
			if (conffile)
				server.set_location(conffile, value);
			//std::cout << "location " << i << std::endl;
			//std::cout << "Error page: " << server.get_location()[i].get_error_page() << std::endl;
			i++;
		}
		if (key == "listen")
			server.set_host_port(value);
		else if (key == "client_max_body_size")
			server.set_body_size(value);
		if (key == "autoindex")
			server.set_autoindex(value);
		else if (key == "root")
		{
			server.set_root(value);
			//std::cout << "Root: " << server.get_root() << std::endl;
		}
		else if (key == "error_page")
			server.set_error_page(value);
	}
	return server;
}
