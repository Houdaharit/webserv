#include <iostream>
#include <fstream>
#include <string>

void test_fct(std::ifstream& confile)
{
	std::string line;
	while (getline(confile, line))
		std::cout << line << std::endl;
}

int main(int argc, char** argv)
{
	if (argc == 2)
	{
		std::ifstream conffile;
		std::string line;

		conffile.open(argv[1]);
		while (getline(conffile, line))
		{
			if (line.find("port") != std::string::npos)
			{
				test_fct(conffile);
			}
		}

	}
	return 0;
}
