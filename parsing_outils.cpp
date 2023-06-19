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
    int i = 0;
    while(str[i] == ' ' || str[i] == '\t')
        i++;
    str = str.substr(i);
}

void trim_back(std::string& str)
{
	std::size_t pos;

	pos = str.find_last_of(' ');
	if (pos == std::string::npos)
		return ;
	else
		str = str.substr(0, pos);
}
