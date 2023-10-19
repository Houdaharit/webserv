#include "../webserv.hpp"

void set_key_value(std::string& line, std::string& key, std::string& value)
{
	std::size_t pos = 0;

	trim_front(line);
	while (pos < line.size() && (line[pos] != ' ' && line[pos] != '\t' && line[pos] != '{'))
		pos++;
	if (pos < line.size())
	{
		key = line.substr(0, pos);
		value = line.substr(pos + 1);
		std::size_t pos_ = value.find(';');
		if (pos_ != std::string::npos)
			value = value.erase(pos_, 1);
		pos_ = value.find('{');
		if (pos_ != std::string::npos)
			value = value.erase(pos_, 1);
		str_trim(value);
		str_trim(key);
	}
	else
		key = line;
}

void ParseConf::read_file(std::ifstream& conffile)
{
	std::string line;
	std::string key;
	std::string value;
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
				this->servers.push_back(parse_server(conffile));
		}
	}
//std::cout << "SERVER Port: " << this->servers[1].get_port() << std::endl;
}

void ParseConf::parsing(int argc, char **argv)
{
	std::ifstream conffile;

	if (!check_file(conffile, argc, argv))
	{
		read_file(conffile);
		conffile.close();
	}
}

std::vector<Server>& ParseConf::get_servers()
{
	return (this->servers);
}
