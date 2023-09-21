#include "../webserv.hpp" 

Location::Location()
{
	this->path = "";
	this->root = "";
	this->index = "";
	this->try_file = "";
	this->redirection = "";
	this->redirect = 0;
	this->fastcgi_pass = "";
	this->errorPage = "";
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

void Location::set_errorPage(std::string& error)
{
	size_t pos = 0;
	size_t i = 0;

	while (pos < error.size())
	{
		while (pos < error.size() && error[pos] != ' ' && error[pos] != '\t')
			pos++;
		std::string tmp = error.substr(i, pos - i);
		if (isNumber(tmp))
		this->statusCode.push_back(atoi(tmp.c_str()));
		else
			this->errorPage = tmp;
		while (pos < error.size() && (error[pos] == ' ' || error[pos] == '\t'))
			pos++;
		i = pos;
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
		this->methods.push_back(tmp);
		while (pos < methods.size() && (methods[pos] == ' ' || methods[pos] == '\t'))
			pos++;
		i = pos;
	}
}

void Location::set_upload(std::string& upload)
{
	this->upload = upload;
}

std::vector<std::string>& Location::get_methods()
{
	return (this->methods);
}

std::string& Location::get_root()
{
	return (this->root);
}

std::string& Location::get_index()
{
	return (this->index);
}

std::string& Location::get_errorPage()
{
	return (this->errorPage);
}

std::string& Location::get_redirection()
{
	return (this->redirection);
}

std::vector<int>& Location::get_statusCode()
{
	return (this->statusCode);
}

int& Location::get_redirect()
{
	return (this->redirect);
}

std::string& Location::get_path()
{
	return (this->path);
}

std::string& Location::get_upload()
{
	return (this->upload);
}
