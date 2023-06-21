#include "webserv.hpp"

void set_server(Server& server, std::string& key, std::string& value)
{
	if (key == "listen")
	{
		std::size_t pos = value.find(':');
		if (pos != std::string::npos)
		{
			server.set_host(value.substr(0, pos));
			server.set_port(value.substr(pos + 1));
		} 
	}
	else if (key == "root")
	{
		//set root
	}
}
void set_key_value(std::string& line, std::string& key, std::string& value)
{
	std::size_t pos = 0;

	trim_front(line);
	while (pos < line.size() && (line[pos] != ' ' && line[pos] != '\t'))
		pos++;
	if (pos < line.size())
	{
		key = line.substr(0, pos);
		value = line.substr(pos+1);
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

	set_key_value(line, key, value);
	set_server(server, key, value);
	//std::cout << "key: " << key << " value: " << value << std::endl;
	return server;
}

void read_file(std::ifstream& conffile)
{
	std::string line;

	while (getline(conffile, line))
	{
		while (line == "")
			getline(conffile, line);
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
