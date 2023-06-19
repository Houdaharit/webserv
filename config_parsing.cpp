#include "webserv.hpp"

void read_file(std::ifstream& conffile)
{
	std::string line;

	getline(conffile, line);
	while (line == "")
		getline(conffile, line);
	std::cout << "line: " << line << std::endl;
}

int check_conf_file(int argc, char** argv)
{
	std::ifstream conffile;

	if (argc == 1)
	{
		std::cout << "No config file!" << std::endl;
		return -1;
	}
	else if (argc == 2)
	{
		conffile.open(argv[1]);
		if (!conffile)
		{
			std::cout << "No such file or permission denied!" << std::endl;
			return -1;
		}
		else
			conffile.close();
	}
	else
	{
		std::cout << "Entre only one config file!" << std::endl;
		return -1;
	}
	return 0;
}

void conf_parsing(int argc, char **argv)
{
	std::cout << "Return: " << check_conf_file(argc, argv) << std::endl;
}

int main(int argc, char** argv)
{
	conf_parsing(argc, argv);
	return 0;
}
