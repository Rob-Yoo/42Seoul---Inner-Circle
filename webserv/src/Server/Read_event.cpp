#include "Server.hpp"

int Server::client_read(int fd)
{
	Client *cli = clients_info[fd];
	int ret = cli->read_client_request();

	if (ret < 0)
	{
		disconnect_client(fd);
		return (-1);
	}
	else if (ret == 0)
		return (0);
	{
		// execute_client_request에서 응답코드가 정해지면, Response, content까지 채운다.
		// execute_client_request의 리턴값이 음수면 바로 change_events + return
		// ====================================================================
		// 이름 validate으로 바꿀 것.
		// 여기서 걸러진 요청은 바로 write할 수 있게 바꿔야 한다.
		execute_client_request(cli->getFd());
		int ret = 0;
		// Response 생성 및 필요한 인자 전달.
		cli->setResponse(new Response(cli->getRequest()->getStatusCode()));

		// 검증단계에서 응답코드가 정해진 것들은 바로 응답한다.
		if (cli->getRequest()->getStatusCode() != 0)
		{
			// 에러페이지 반환
			if (cli->getRequest()->getStatusCode() == 400)
			{
				cli->getResponse()->setContent("Bad Request");
				change_events(cli->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
			}
			else if (cli->getRequest()->getStatusCode() / 100 == 4)
			{
				ret = cli->getResponse()->openFile(cli->getRequest()->getSerBlock().getRootDir() + "/" + cli->getRequest()->getSerBlock().getErrorPage(), O_RDONLY);
				file_to_client[ret] = cli->getFd();
				change_events(ret, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
			}
			// 리디렉션
			else if (cli->getRequest()->getStatusCode() / 100 == 3)
			{
				cli->getResponse()->redirectResponse(cli->getRequest()->getStatusCode(), cli->getRequest()->getRedirectionURL());
				change_events(cli->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
			}

			return 0;
		}
		// 메소드별 실행
		else if (cli->getRequest()->getMethod() == "GET" || cli->getRequest()->getLocBlock().getAutoIndex()){
			ret = cli->GET(cli->getRequest(), cli->getResponse());
		} else if (cli->getRequest()->getMethod() == "DELETE") {
			ret = cli->DELETE(cli->getRequest(), cli->getResponse());
		} else if (cli->getRequest()->getMethod() == "POST") {
			ret = cli->POST(cli->getRequest(), cli->getResponse());
		} else if (cli->getRequest()->getMethod() == "PUT") {
			ret = cli->POST(cli->getRequest(), cli->getResponse());
		} else {
			std::cerr << "Undefined Method" << std::endl;
		}

		if (ret > 2) // 유효한 fd가 반환되었을 경우
		{
			if (cli->is_cgi_request(cli->getRequest())) // Cgi요청인 경우 반환된 fd는 파이프입구fd이다.
			{
				Cgi *cgi = cli->getCgi();
				std::cout << "Pipe returned! registered to kqueue..." << std::endl;
				// 파이프 입구,출구를 목록에 추가한다.
				pipe_to_client[ret] = cli->getFd();
				pipe_to_client[cgi->getToParent()[0]] = cli->getFd();
				change_events(ret, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
			}
			else
			{
				std::cout << "File returned! registered to kqueue..." << std::endl;
				file_to_client[ret] = cli->getFd();

				if (cli->getResponse()->getFdMode(ret) == O_RDONLY)
					change_events(ret, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
				else
				{
					// 업로드할 데이터의 내용은 req's body이다.
					cli->getResponse()->setContent(cli->getRequest()->getReqBody());
					change_events(ret, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
				}
			}
		}
		else
			change_events(cli->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	}
	return 0;
}

int Server::pipe_read(int fd)
{
	std::cout << "pipe read event" << std::endl;
	Client *cli = clients_info[pipe_to_client[fd]];

	// 파이프 출구를 read
	if (cli->read_pipe_result() == 0 )
		return (0);

	// 파이프 출구를 폐기
	disconnect_pipe(cli->getPipeFd());

	// 클라이언트 WRITE 이벤트 설정(HTTP Response 허용)
	change_events(cli->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	return 0;
}

int Server::file_read(int fd, intptr_t datalen)
{
	std::cout << "file read event" << std::endl;
	std::cout << "you have [" << datalen << "] byte left to read" << std::endl;

	Client *cli = clients_info[file_to_client[fd]];
	Request* req = cli->getRequest();
	Response* res = cli->getResponse();

	// 읽기가 완성되지 않았다면 로직중지.
	if (!res->readFile(fd, datalen))
		return 0;

	//if (req->is_valid_request(req->getStatusCode()) && cli->is_cgi_request(req))
	if ((req->getStatusCode() / 100 != 4 || req->getStatusCode() / 100 != 5)  && cli->is_cgi_request(req))
	{
		Cgi* cgi = cli->getCgi();
		// 파이프 입구도 pipe_to_client에 등록되어 있어야함!!!

		// 다음단계 : 파이프에 데이터를 입력
		change_events(cgi->getToChild()[1], EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	}
	else // 다음단계 : HTTP 응답
		change_events(cli->getFd(), EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	return 0;
}
