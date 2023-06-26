#include "webserv.hpp"

void parse_location(Location& location, std::string& key, std::string& value)
{
	if (key == "root")
		location.set_root(value);
	else if (key == "index")
		location.set_index(value);
	else if (key == "error_page")
		location.set_error_page(value);
	else if (key == "limit_except")
		location.set_methods(value);
	else if (key == "return")
		location.set_redirection(value);
}
