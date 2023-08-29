#include "../webserv.hpp"

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
		//A discuter
		/*		pos_ = value.find('{');
				if (pos_ != std::string::npos)
				value = value.erase(pos_, 1);*/
		str_trim(value);
		str_trim(key);
	}
	else
		key = line;
}

void read_file(std::ifstream& conffile)
{
	std::string line;
	std::string key;
	std::string value;
	ParseConf config;

	while (getline(conffile, line))
	{
		while (line == "")
		{
			if (!getline(conffile, line))
				return ;
		}
		set_key_value(line, key, value);
		if (key == "server")
		{
			if (conffile)
				config.servers.push_back(parse_server(conffile));
		}
	}	
}

void conf_parsing(int argc, char **argv)
{
	std::ifstream conffile;

	if (!check_file(argc, argv))
	{
		conffile.open(argv[1]);
		read_file(conffile);
		conffile.close();
	}
}

/*int main(int argc, char** argv)
{
	Server server;
	conf_parsing(argc, argv);
	return (0);
}*/
