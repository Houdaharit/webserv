#include "webserv.hpp"

void set_key_value(std::string& line, std::string& key, std::string& value)
{
	std::size_t pos = 0;

	trim_front(line);
	while (pos < line.size() && (line[pos] != ' ' && line[pos] != '\t'))
		pos++;
	if (pos < line.size())
	{
		key = line.substr(0, pos);
		value = line.substr(pos + 1);
		std::size_t pos_ = value.find(';');
		if (pos_ != std::string::npos)
			value = value.erase(pos_, 1);
		str_trim(value);
		str_trim(key);
	}
	else
		key = line;
}

Server parsing(std::string& line)
{
	std::string key("");
	std::string value("");
	Server server;
	Location location;

	set_key_value(line, key, value);
	//std::cout << "key: " << key << " value: " << value << std::endl;
	parse_server(server, key, value);
	parse_location(location, key, value);
	return server;
}

void read_file(std::ifstream& conffile)
{
	std::string line;

	while (getline(conffile, line))
	{
		while (line == "")
		{
			if (!getline(conffile, line))
				return ;
		}
		parsing(line);
	}	
}

void conf_parsing(int argc, char **argv)
{
	std::ifstream conffile;

	if (!check_conf_file(argc, argv))
	{
		conffile.open(argv[1]);
		read_file(conffile);
		conffile.close();
	}
}

int main(int argc, char** argv)
{
	Server server;
	conf_parsing(argc, argv);
	return (0);
}
