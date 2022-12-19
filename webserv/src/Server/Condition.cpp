#include "Server.hpp"

int Server::is_listensocket(int fd)
{
	for (map<int, int>::iterator iter = fd_to_port.begin() ; iter !=  fd_to_port.end(); iter++)
		if (fd == iter->first)
			return 1;
	return 0;
}

int Server::is_client(int fd)
{
	if (clients_info.find(fd) != clients_info.end())
		return 1;
	return 0;
}

int Server::is_pipe(int fd)
{
	if (pipe_to_client.find(fd) != pipe_to_client.end())
		return 1;
	return 0;
}

int Server::is_file(int fd)
{
	if (file_to_client.find(fd) != file_to_client.end())
		return 1;
	return 0;
}
