#include "Location.cpp"

void Location::set_root(std::string& root)
{
	this->root = root;
}

void Location::set_index(std::string& index)
{
	this->index = index;
}

void Location::set_error_page(std::string& error)
{
	size_t pos = 0;

	while (pos < error.size() && error[pos] != ' ' && error[pos] != '\t')
		pos++;
	if (pos < error.size())
	{
		this->error = atoi(error.substr(0, pos).c_str());
		this->error_page = error.substr(pos + 1);
		str_trim(this->error_page);
	}
}

void Location::set_redirection(std::string& redir)
{
    size_t pos = 0;

    while (pos < error.size() && error[pos] != ' ' && error[pos] != '\t')
        pos++;
    if (pos < error.size())
    {
        this->redirect = atoi(error.substr(0, pos).c_str());
        this->redirection = error.substr(pos + 1);
        str_trim(this->redirection);
    }
}

void Location::set_methods(std::string& methods)
{

}
