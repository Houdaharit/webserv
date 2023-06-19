#include "webserv.hpp"

Server parsing(std::string& line)
{
	std::size_t pos;
	std::string key;
	std::string value;
	Server server;

	pos = line.find(' ');
	if (pos == std::string::npos)
		pos = line.find('\t');
	if (pos == std::string::npos)
		pos = line.find('\r');
	if (pos == std::string::npos)
		pos = line.find('\f');
	if (pos == std::string::npos)
		pos = line.find('\v');
	key = line.substr(0, pos);
	value = line.substr(pos+1);
	/*trim_front(value);
	trim_back(value);
	trim_back(key);*/
	std::cout << "key: " << key << " value: " << value << std::endl;
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
		//	std::cout << line << std::endl;
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
