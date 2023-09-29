#include "../webserv.hpp"

Location parse_location(std::ifstream& confile, std::string& path)
{
	std::string key, value, line;
	Location location;

	location.set_path(path);
	while (getline(confile, line))
	{
		set_key_value(line, key, value);
		if (key == "}")
			break;
		if (key == "root")
			location.set_root(value);
		else if (key == "index")
			location.set_index(value);
		else if (key == "error_page")
			location.set_errorPage(value);
		else if (key == "limit_except")
			location.set_methods(value);
		else if (key == "return")
			location.set_redirection(value);
		else if (key == "upload")
			location.set_upload(value);
	}
	return location;
}
