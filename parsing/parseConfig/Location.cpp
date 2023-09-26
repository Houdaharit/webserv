#include "../webserv.hpp" 

Location::Location()
{
	this->path = "";
	this->root = "";
	this->try_file = "";
	this->redirection = "";
	this->redirect = 0;
	this->fastcgi_pass = "";
	this->autoindex = "OFF";
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
	size_t pos = 0;
	size_t i = 0;

	while (pos < index.size())
	{
		while (pos < index.size() && index[pos] != ' ' && index[pos] != '\t')
			pos++;
		std::string tmp = index.substr(i, pos - i);
		this->index.push_back(tmp);
		while (pos < index.size() && (index[pos] == ' ' || index[pos] == '\t'))
			pos++;
		i = pos;
	}
}

void Location::set_errorPage(std::string& error)
{
	size_t pos = 0;
	size_t i = 0;
	std::vector<std::string> statusCode;
	std::string errorPage;
	std::pair<std::vector<std::string>, std::string> errors;

	while (pos < error.size())
	{
		while (pos < error.size() && error[pos] != ' ' && error[pos] != '\t')
			pos++;
		std::string tmp = error.substr(i, pos - i);
		if (isNumber(tmp))
			statusCode.push_back(tmp.c_str());
		else
			errorPage = tmp;
		while (pos < error.size() && (error[pos] == ' ' || error[pos] == '\t'))
			pos++;
		i = pos;
	}
	errors.first = statusCode;
	errors.second = errorPage;
	this->errorPage.push_back(errors);
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

void Location::set_autoindex(std::string& autoindex)
{
        this->autoindex = autoindex;
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

std::vector<std::string>& Location::get_index()
{
	return (this->index);
}

std::vector<std::pair<std::vector<std::string>, std::string> >& Location::get_errorPage()
{
	return (this->errorPage);
}

std::string& Location::get_redirection()
{
	return (this->redirection);
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

std::string& Location::get_autoindex()
{
        return (this->autoindex);
}
