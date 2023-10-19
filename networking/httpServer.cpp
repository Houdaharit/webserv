#include "httpServer.hpp"

// void HttpServer::CheckRequestStatus(Client &client) {
// 	HttpRequest &client_request = client.getRequest();

// 	if (client_request.getRequestState() == HttpRequest::HEADER_STATE) {
// 		getHeader(client_request);
// 	}
// 	if (client_request.getRequestState() == HttpRequest::BODY_STATE)  {

// 		if (client_request.getRequestData().size() > client.getServer().getClientMaxBodySize())
// 				throw(RequestError(ErrorNumbers::_413_PAYLOAD_TOO_LARGE));
// 		client_request.openDataFile();
// 		if (client_request.getBodyTransferType() == HttpRequest::CHUNKED) {
// 			while (!client_request.getRequestData().empty() && unchunkBody(client_request)) {
// 			}
// 		}
// 		else if (client_request.getBodyTransferType() == HttpRequest::CONTENT_LENGHT) {
// 			if (getBody(client_request))  {
// 				client_request.setRequestState(HttpRequest::REQUEST_READY);
// 			}
// 		}
// 		else
// 			throw(RequestError(411));
// 	}
// 	if (client_request.getRequestState() == HttpRequest::REQUEST_READY)  {
// 		FD_SET(client.getConnectionFd() , &(this->_writeset));
// 		const Server & client_server = getServerByName(client_request.getHeaderValue("Host")); // Supports virtual hosting
// 		client.setServer(client_server);
// 		#if DEBUG
// 		ConsoleLog::Debug("server handeling the request : " + client.getServer().getServerName());
// 		#endif
// 	}
// }

void HttpServer::CheckRequestStatus(Client &client)
{
	HttpRequest &request = client.getRequest();
	std::string &request_data = request.getRequestData();
	std::string CRLF_delim("\r\n\r\n");
	size_t pos;

	if (request.get_requestStatus() == HttpRequest::HEADERS)
	{
		pos = request_data.find(CRLF_delim);
		if (pos != std::string::npos)
			request.parse(request_data);
		if (request_data.empty() && (request.get_httpMethod() == "GET" || request.get_httpMethod() == "DELETE"))
			request.set_requestStatus(HttpRequest::REQUEST_READY);
	}
	if (request.get_requestStatus() == HttpRequest::BODY)
	{
		request.is_body();
		if (request.set_body(request_data))
			request.set_requestStatus(HttpRequest::REQUEST_READY);
	}
}

HttpServer::HttpServer(ParseConf &pars) : Config(pars), Vserver(pars.get_servers()), MaxFd(0)
{
	std::vector<Server> &servers = this->Config.get_servers();
	const int true_ = 1;
	int sock_fd;

	FD_ZERO(&(this->WriteSet));
	FD_ZERO(&(this->ReadSet));
	FD_ZERO(&(this->ServerSet));

	for (ParseConf::v_iterator server = servers.begin(); server != servers.end(); server++)
	{
		// std::cout << "HELLO FROM SERVER" << server->get_port() << std::endl;
		sock_fd = Network::CreateSocket();
		setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &true_, sizeof(int));
		Network::BindSocket(sock_fd, server->get_port(), server->get_host());
		Network::ListenOnSocket(sock_fd);
		addSocketFd(sock_fd);
		FD_SET(sock_fd, &(this->ServerSet));
		{
			std::stringstream ss;
			ss << server->get_port();
			std::string port = ss.str();
			const std::string logs = "Serving HTTP on " + server->get_host() + " Port: " + port;
			log(logs);
		}
		server->set_Socket(sock_fd);
	}
}

void HttpServer::addSocketFd(int fd)
{
	this->_server_fds.push_back(fd);
	FD_SET(fd, &(this->ReadSet));
}
HttpServer::~HttpServer()
{
	for (std::vector<int>::iterator it = _server_fds.begin(); it != _server_fds.end(); it++)
		close(*it);
}

void HttpServer::RunServer()
{
	fd_set read_copy;
	fd_set write_copy;
	while (1)
	{
		read_copy = this->ReadSet;
		write_copy = this->WriteSet;
		this->MaxFd = *std::max_element(this->_server_fds.begin(), this->_server_fds.end());
		selectServer(read_copy, write_copy);
	}
}

Client &HttpServer::GetRightClient(int fd)
{
	iteratorCl it = this->Mclient.find(fd);
	if (it != this->Mclient.end())
		return (it->second);
	else
		throw(ClientError("BUG: Potential Server error"));
}

void Client::saveRequestData(size_t nb_bytes)
{
	std::string str_bytes(this->_buffer, nb_bytes);
	this->CRequest.setRequestData(str_bytes);
}

void HttpServer::CloseConnection(int fd)
{
	FD_CLR(fd, &this->ReadSet);
	FD_CLR(fd, &this->WriteSet);
	this->Mclient.erase(fd);
	this->_server_fds.erase(std::find(_server_fds.begin(), _server_fds.end(), fd));
	close(fd);
	log("Closing connection\n");
}

void HttpServer::readRequest(int fd)
{
	Client &client = GetRightClient(fd);
	char *buffer = client._buffer;
	size_t client_buffer_size = sizeof(client._buffer);
	size_t bytes_recieved;

	bzero(buffer, client_buffer_size);
	bytes_recieved = read(client.getConnectionFd(), buffer, client_buffer_size - 1);
	if (bytes_recieved <= 0)
	{
		if (bytes_recieved == 0)
		{
			Network::closeConnection(fd);
			CloseConnection(fd);
			FD_CLR(fd, &(this->ReadSet));
			return;
		}
	}
	client.saveRequestData(bytes_recieved);
	CheckRequestStatus(client);
	if (client.getRequest().get_requestStatus() == HttpRequest::REQUEST_READY)
	{
		const Server &clientServer = MatchServerbyName(client.getRequest().get_headers()["Host"]);
		client.setServer(clientServer);
		FD_SET(fd, &this->WriteSet);
	}
}

void HttpServer::selectServer(fd_set &Readcpy, fd_set &Writecpy)
{
	int max_fd = this->MaxFd;
	if (select(max_fd + 1, &Readcpy, &Writecpy, NULL, NULL) < 0)
	{
		throw(ClientError("Error : multiplexing Error!"));
	}
	for (int fd = 3; fd <= max_fd; fd++)
	{
		try
		{
			if (FD_ISSET(fd, &Writecpy))
			{
				Client &client = GetRightClient(fd);
				sendResponse(client);
			}
			else if (FD_ISSET(fd, &Readcpy))
			{
				if (FD_ISSET(fd, &(this->ServerSet)))
					addClient_to_map(Network::acceptConnection(fd));
				else
					readRequest(fd);
			}
		}
		catch (const RequestError &error)
		{
			FD_CLR(fd, &this->ReadSet);
			FD_SET(fd, &this->WriteSet);
			close(fd);
		}
	}
}

const Server &HttpServer::MatchServerbyFd(int fd)
{
	typedef std::vector<Server>::const_iterator cv_iterator;

	for (cv_iterator server = this->Vserver.begin(); server != this->Vserver.end(); server++)
	{
		if (server->getSocket() == fd)
			return (*server);
	}
	return (*this->Vserver.begin());
}
const Server &HttpServer::MatchServerbyName(std::string host_name)
{
	typedef std::vector<Server>::const_iterator cv_iterator;
	std::string host;
	size_t pos;
	std::ostringstream port;
	bool isLocalhost = false;

	pos = host_name.find(":");
	if (pos != std::string::npos)
	{
		host = host_name.substr(0, pos);
		if (host == "localhost" || host == "127.0.0.1")
			isLocalhost = true;
	}

	for (cv_iterator server = this->Vserver.begin(); server != this->Vserver.end(); server++)
	{
		port << server->get_port();
		if ((server->get_host() == "localhost" || server->get_host() == "127.0.0.1") && isLocalhost)
		{
			host = host_name.substr(pos + 1);

			if (host == port.str())
				return *server;
		}
		else
		{

			std::string serv = server->get_host() + ":" + port.str();
			if (serv == host_name)
				return (*server);
		}
	}
	return (*this->Vserver.begin());
}
void HttpServer::addClient_to_map(Client client)
{
	typedef std::map<int, Client>::value_type pair_t;

	int sock_fd = client.getConnectionFd();
	int server_fd = client.getServerFd();
	client.setServer(MatchServerbyFd(server_fd));
	pair_t pair(sock_fd, client);
	this->Mclient.insert(pair);
	addSocketFd(sock_fd);
}

void HttpServer::sendResponse(Client &client)
{
	Response resp(client);
	resp._Response();
	// std::string RESPONSE = "";
	// int fd = client.getConnectionFd();

	// std::cout << client.HEADER << std::endl;
	// std::cout << client.BODY << std::endl;
	if (client.getHEADER_SENT() == false)
	{
		client.setRESPONSE(client.getHEADER());
		// send(client.getConnectionFd(), client.getRESPONSE().c_str(), client.getRESPONSE().length(), 0);
		// std::cout << client.RESPONSE << std::endl;
		client.setHEADER_SENT(true);
		// return ;
	}

	else
	{
		client.setRESPONSE("");
		if (client.getBODY().length() > 0)
		{
			std::cout << "******************************************************************" << std::endl;
			char buffer[BUFFER_SIZE];

			if (client.getFILE_OPENED() == false)
			{
				// std::cout << "opening the file " << std::endl;
				client.file.open(client.getBODY().c_str(), std::ios::in | std::ios::binary);
				client.setFILE_OPENED(true);
			}
			if (client.file.good())
			{
				client.file.read(buffer, BUFFER_SIZE);
				client.bytes_read = client.file.gcount();
				if (client.bytes_read < 0)
					std::cerr << "ERROR HERE : IN READ BYTES " << std::endl;

				// std::cout << "bytesRead is : =====> " << client.bytes_read << std::endl;
				//  buffer[bytes_read] = '\0';
				client.setRESPONSE(std::string(buffer, client.bytes_read));
			}
			else
			{
				int ss = send(client.getConnectionFd(), client.getBODY().c_str(), client.getBODY().length(), 0);
				if (ss < 0 || ss == (int)client.getBODY().length())
					CloseConnection(client.getConnectionFd());
				return;
			}
			// if(client.getFILE_OPENED() == true)
			// {
			// 	client.file.close();
			// 	client.setFILE_OPENED(false);
			// }
		}
	}
	// std::cout << client.getRESPONSE() << std::endl;
	int result = send(client.getConnectionFd(), client.getRESPONSE().c_str(), client.getRESPONSE().length(), 0);

	client.bytes_sent += result;

	// std::cout << "RESPONSE size !!!!!!! : " << result << std::endl;

	// std::cout << client.getConnectionFd() << std::endl;

	if (result <= 0)
	{
		CloseConnection(client.getConnectionFd());
		if (result < 0)
			std::cout << "send failed \n";
	}
}
