#include "Server.hpp"

int Server::client_write(int fd)
{
	Client *cli = clients_info[fd];
	// CGI process 종료상태 회수
	if (cli->is_cgi_request(cli->getRequest()))
		waitpid(cli->getRequest()->getCgiPid(), NULL, 0);

	char *res = strdup(cli->getResponse()->getHttpResponse().c_str());

	// DEBUG Response
	std::cout << "====== response start ======\n" << std::endl;
	std::cout << res << std::endl << std::endl;
	std::cout << "====== response end ======" << std::endl;

	int n;
	if ((n = write(fd, res, strlen(res)) == -1))
		std::cerr << "[DEBUG] client write error!" << std::endl;
	else
		std::cout << "[DEBUG] http response complete" << std::endl;
	free(res);

	// 매 요청을 처리하고 연결을 종료한다.
	disconnect_client(fd);
	return (0);
}

int Server::pipe_write(int fd)
{
	Client *cli = clients_info[pipe_to_client[fd]];
	Response* res = cli->getResponse();
	Cgi* cgi = cli->getCgi();

	if (!res->writeFile(fd, res->getContent().length()))
		return 0;

	pipe_to_client.erase(fd);	// 파이프 입구를 파이프목록에서 삭제
	close(fd);					// 파이프 입구를 close
	change_events(cgi->getToParent()[0], EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	return 0;
}

int Server::file_write(int fd, intptr_t datalen)
{
	Client *cli = clients_info[file_to_client[fd]];
	Response* res = cli->getResponse();

	// file이 Read-only라면, write할 수 없음.
	if (cli->getResponse()->getFdMode(fd) == O_RDONLY)
		return 0;
	bool is_write_done = res->writeFile(fd, datalen);
	if (is_write_done)
		change_events(cli->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	return 0;
}
