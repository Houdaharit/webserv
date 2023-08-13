#include "webserv.hpp" 

Location::Location() : allow_methods()
{
	this->path = "";
	this->root = "";
	this->index = "";
	this->try_file = "";
	this->error = 0;
	this->redirection = "";
	this->redirect = 0;
	this->fastcgi_pass = "";
	this->error_page = "";
}

Location::~Location()
{
//	std::cout << "bye(Location)" << std::endl;
}
void Location::set_path(std::string& path)
{
	this->path = path;
}

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

	while (pos < redir.size() && redir[pos] != ' ' && redir[pos] != '\t')
		pos++;
	if (pos < redir.size())
	{
		this->redirect = atoi(redir.substr(0, pos).c_str());
		this->redirection = redir.substr(pos + 1);
		str_trim(this->redirection);
	}
}

void Location::set_methods(std::string& methods)
{
	size_t pos = 0;
	size_t i = 0;

	while (pos < methods.size())
	{
		while (pos < methods.size() && methods[pos] != ' ' && methods[pos] != '\t')
			pos++;
		std::string tmp = methods.substr(i, pos - i);
		this->allow_methods.push_back(tmp);
		while (pos < methods.size() && (methods[pos] == ' ' || methods[pos] == '\t'))
			pos++;
		i = pos;
	}
}

std::vector<std::string>& Location::get_methods()
{
	return (this->allow_methods);
}

std::string& Location::get_root()
{
	return (this->root);
}

std::string& Location::get_index()
{
	return (this->index);
}

std::string& Location::get_error_page()
{
	return (this->error_page);
}

std::string& Location::get_redirection()
{
	return (this->redirection);
}

int& Location::get_error()
{
	return (this->error);
}

int& Location::get_redirect()
{
	return (this->redirect);
}

std::string& Location::get_path()
{
	return (this->path);
}
