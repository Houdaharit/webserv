#include "webserv.hpp"

void parse_server(Server& server, std::ifstream& conffile)
{
    if (key == "listen")
        server.set_host_port(value);
    else if (key == "client_max_body_size")
        server.set_body_size(value);
    if (key == "autoindex")
        server.set_autoindex(value);
    else if (key == "root")
        server.set_root(value);
    else if (key == "error_page")
        server.set_error_page(value);
}
