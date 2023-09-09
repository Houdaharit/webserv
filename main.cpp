#include "webserv.hpp"

int main(int argc, char **argv)
{
	std::string str("Hello ");
	std::string str1("everyone!");
	str = str + str1;
	std::cout << str << std::endl;
	//config_parsing(argc, argv);
	return (0);
}
