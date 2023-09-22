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
			location.set_errorPage(value);
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
		else if (key == "upload")
		{
			location.set_upload(value);
		//	std::cout << "upload: "<< location.get_upload() << std::endl;
		}
	}
	return location;
}
