#include "webserv.hpp"

void set_key_value(std::string& line, std::string& key, std::string& value)
{
	std::size_t pos = 0;

	while (pos < line.size() && (line[pos] != ' ' && line[pos] != '\t'))
		pos++;
	if (pos < line.size())
	{
		key = line.substr(0, pos);
		value = line.substr(pos+1);
		trim_front(value);
		trim_back(value);
		trim_back(key);
	}
	else
		key = line;
}

Server parsing(std::string& line)
{
	std::string key;
	std::string value;
	Server server;

	set_key_value(line, key, value);
	return server;
}

void read_file(std::ifstream& conffile)
{
	std::string line;

	while (getline(conffile, line))
	{
		while (line == "")
			getline(conffile, line);
		trim_front(line);
		parsing(line);
	}	
}

void conf_parsing(int argc, char **argv)
{
	std::ifstream conffile;

	if (check_conf_file(argc, argv) == 0)
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
