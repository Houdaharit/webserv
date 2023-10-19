/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_linux.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AAIT-MAS <AAIT-MAS@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:02:15 by ahakam            #+#    #+#             */
/*   Updated: 2023/10/13 16:51:51 by AAIT-MAS         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "httpServer.hpp"

int main(int argc, char **argv)
{
    try
    {
        signal(SIGPIPE, SIG_IGN);
        ParseConf pars;
        pars.parsing(argc,argv);
        HttpServer server(pars);
        server.RunServer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }   
}