#include "webserv.hpp"

void parse_location(Location& location, std::string& key, std::string& value)
{
	if (key == "location")
	{
		location.set_path(value);
		//std::cout << "PATH: " << location.get_path() << std::endl;
	}
	if (key == "root")
	{
		location.set_root(value);
		//std::cout << "root: " << location.get_root() << std::endl;
	}
	else if (key == "index")
	{
		location.set_index(value);
		//std::cout << "index: "<< location.get_index() << std::endl;
	}
	else if (key == "error_page")
	{
		location.set_error_page(value);
		//std::cout << "error page: " << location.get_error_page() << std::endl;
	}
	else if (key == "limit_except")
	{
		location.set_methods(value);
		//for(size_t i = 0; i < location.get_methods().size(); i++)
		//std::cout << "methods: " << location.get_methods()[i] << std::endl;
	}
	else if (key == "return")
	{
		location.set_redirection(value);
		//std::cout << "redirection: " << location.get_redirection() << std::endl;
	}
}
