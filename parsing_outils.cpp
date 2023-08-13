#include "webserv.hpp"

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

void trim_front(std::string& str)
{
	std::size_t i = 0;
	while(i < str.size() && (str[i] == ' ' || str[i] == '\t'))
		i++;
	str = str.substr(i);
}

void trim_back(std::string& str)
{
	std::size_t pos;

	pos = str.size();
	while (pos > 1 && (str[pos - 1] == ' ' || str[pos - 1] == '\t'))
		pos--;
	if (pos == 1)
		return ;
	//sus error
	str = str.substr(0, pos);
}

void str_trim(std::string& str)
{
	trim_front(str);
	trim_back(str);
}
