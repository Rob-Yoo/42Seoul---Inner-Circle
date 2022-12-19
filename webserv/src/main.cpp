#include "Config/LocationBlock.hpp"
#include "Config/ServerBlock.hpp"

// Server side C program to demonstrate Socket programming
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/event.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <map>
#include <vector>
#include <iostream>

#include "Request/Request.hpp"
#include "Config/Config.hpp"
#include "Server/Server.hpp"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		Server server(argv[1]);
		server.init_multiplexing();
		server.run();
	}
	else if (argc == 1)
	{
		Server server("config/default.config");
		server.init_multiplexing();
		server.run();
	}
	else
		cerr << "Execute webserv program with one argument or without argument.\n";
	return 0;
}
