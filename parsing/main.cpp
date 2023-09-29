#include "webserv.hpp"

int main(int argc, char **argv)
{
	ParseConf config;
	config.parsing(argc, argv);
	return (0);
}
