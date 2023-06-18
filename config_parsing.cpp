#include "webserv.hpp"

void read_file(std::ifstream& conffile)
{
	std::cout << "Read file!" << std::endl;
}

void conf_parsing(int argc, char **argv)
{
	std::ifstream conffile;

	if (argc == 1)
		std::cout << "No config file!" << std::endl;
	else if (argc == 2)
	{
		conffile.open(argv[1]);
		if (!conffile)
			std::cout << "No such file or permission denied!" << std::endl;
		else
			read_file(conffile);
	}
}

int main(int argc, char** argv)
{
	conf_parsing(argc, argv);
	return 0;
}
