#include "Server.hpp"

void Server::exit_with_perror(const string& msg)
{
	std::cerr << msg << std::endl;
	exit(EXIT_FAILURE);
}

int Server::callback_error(int fd)
{
	if (is_listensocket(fd))
		exit_with_perror("server socket error");
	else if (is_client(fd))
	{
		std::cerr << "Client socket[" << fd << "] got error" << std::endl;
		disconnect_client(fd);
	}
	else if (is_pipe(fd))
	{
		std::cerr << "Pipe socket[" << fd << "] got error" << std::endl;
		change_events(pipe_to_client[fd], EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
		Client* cli = clients_info[pipe_to_client[fd]];
		cli->getResponse()->setStatusCode(500);
		cli->getResponse()->setContent("Pipe Error");
		disconnect_pipe(fd);
	}
	else if (is_file(fd))
	{
		std::cerr << "File fd[" << fd << "] got error" << std::endl;
		change_events(file_to_client[fd], EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
		Client* cli = clients_info[file_to_client[fd]];
		cli->getResponse()->setStatusCode(500);
		cli->getResponse()->setContent("Regular file fd Error");
		file_to_client.erase(fd);
		close(fd);
	}
	return 0;
}

int Server::callback_read(int fd, intptr_t datalen)
{
	if (is_listensocket(fd))
		connect_new_client(fd);
	else if (is_client(fd))
		client_read(fd);
	else if (is_pipe(fd))
		pipe_read(fd);
	else if (is_file(fd))
		file_read(fd, datalen);
	return (0);
}

int Server::callback_write(int fd, intptr_t datalen)
{
	if (is_client(fd))
		client_write(fd);
	else if (is_pipe(fd))
		pipe_write(fd);
	else if (is_file(fd))
		file_write(fd, datalen);
	return (0);
}

void Server::disconnect_pipe(int pipe_fd)
{
	if (pipe_to_client.find(pipe_fd) == pipe_to_client.end())
	{
		std::cout << "There's no pipe that you want to delete!\n";
		return ;
	}
	else if (clients_info.find(pipe_to_client[pipe_fd]) == clients_info.end())
	{
		std::cout << "There's no client that owns that pipe!\n";
		return ;
	}
	// 클라이언트의 파이프fd를 유효하지 않게 바꾼다.
	Client *cli = clients_info[pipe_to_client[pipe_fd]];
	cli->setPipeFd(-1);
	Cgi* cgi = clients_info[pipe_to_client[pipe_fd]]->getCgi();
	if (cgi)
	{
		close(cgi->getToChild()[1]);
		close(cgi->getToParent()[0]);
		pipe_to_client.erase(cgi->getToChild()[1]);
		pipe_to_client.erase(cgi->getToParent()[0]);
	}
	delete cgi;
	cli->setCgi(0);
}

void Server::disconnect_client(int client_fd)
{
	close(client_fd);
	Client *cli = clients_info[client_fd];
	if (cli->getCgi())
	{
		close(cli->getCgi()->getToChild()[1]);
		close(cli->getCgi()->getToParent()[0]);
		pipe_to_client.erase(cli->getCgi()->getToChild()[1]);
		pipe_to_client.erase(cli->getCgi()->getToParent()[0]);
	}
	if (clients_info[client_fd]->getPipeFd() != -1)
		disconnect_pipe(clients_info[client_fd]->getPipeFd());

	delete cli->getResponse();
	delete cli->getRequest();
	cli->setRequest(0);
	cli->setResponse(0);
	delete clients_info[client_fd];
	clients_info.erase(client_fd);
	std::cout << "[DEBUG]client disconnected: " << client_fd << std::endl;
}

void Server::change_events(uintptr_t ident, int16_t filter,
		uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
	struct kevent temp_event;

	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	change_list.push_back(temp_event);
}

int Server::connect_new_client(int fd)
{
	int			client_socket;
	sockaddr_in	client_addr;
	socklen_t	client_len;

	// 클소켓을 change_list에 읽쓰이벤트로 등록
	if ((client_socket = accept(fd, (sockaddr*)&client_addr, &client_len)) == -1)
		exit_with_perror("accept error");
	std::cout << "[DEBUG]client socket[" << client_socket << "] just connected" << std::endl;

	// client 정보 등록
	clients_info[client_socket] = new Client(client_socket, client_addr, client_len);

	// kqueue로부터 읽기 이벤트 감지
	change_events(client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	return (0);
}
