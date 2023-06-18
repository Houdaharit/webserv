#include "webserver.hpp"

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
	}
}
