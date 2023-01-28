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
using namespace std;

void exit_with_perror(const string& msg)
{
	cerr << msg << endl;
	exit(EXIT_FAILURE);
}

void disconnect_client(int client_fd, map<int, string>& clients)
{
	cout << "client disconnected: " << client_fd << endl;
	close(client_fd);
	clients.erase(client_fd);
}

void change_events(vector<struct kevent>& change_list, uintptr_t ident, int16_t filter,
		uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
	struct kevent temp_event;

	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	change_list.push_back(temp_event);
}

void SendErrorMSG(int sock)
{
	char protocol[] = "HTTP/1.0 400 Bad Request\r\n";
	char servName[] = "Server:simple web server\r\n";
	char cntLen[] = "Content-length:2048\r\n";
	char cntType[] = "Content-type:text/html\r\n\r\n";
	char content[] = "<html><body><h1>You got Error!</h1></body></html>";

	send(sock, protocol, strlen(protocol), 0);
	send(sock, servName, strlen(servName), 0);
	send(sock, cntLen, strlen(cntLen), 0);
	send(sock, cntType, strlen(cntType), 0);
	send(sock, content, strlen(content), 0);
	close(sock);
}

int main(int argc, char **argv)
{
	// for tcp/ip
	int server_fd, new_socket; long valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	// for kqueue
	struct	kevent event;	 /* 감시대상 이벤트 */
	struct	kevent tevent;	 /* Event triggered */
	int kq, ret;
	// 필요?
	int flags;
	struct timespec timeout = { 0, 0 };

	if (argc != 2)
		err(EXIT_FAILURE, "Usage: %s <Port>\n", argv[0]);

	// 서버소켓 셋팅.
	{
		// 소켓 생성
		if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		{
			perror("In socket");
			exit(EXIT_FAILURE);
		}

		// 주소 구조체에 서버의 IP,PORT 저장
		memset(address.sin_zero, 0, sizeof(address.sin_zero));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons( atoi(argv[1]) );

		// Bind
		if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
		{
			perror("In bind");
			exit(EXIT_FAILURE);
		}
		// Listen
		if (listen(server_fd, 10) < 0)
		{
			perror("In listen");
			exit(EXIT_FAILURE);
		}
	}

	// kqueue 셋팅
	{
		/* Create kqueue. */
		kq = kqueue();
		if (kq	== -1)
			err(EXIT_FAILURE, "kqueue() failed");

		/* Initialize kevent structure. */
		// kev, ident, filter, flags, fflags, data, udata
		EV_SET(&event, server_fd, EVFILT_READ, EV_ADD | EV_CLEAR, flags,
			0,	NULL);

		/* Attach event to the	kqueue.	*/
		// kq, changelist, nchanges, eventlist, nevents, timeout
		ret = kevent(kq, &event, 1, NULL, 0, NULL);
		printf("kevent ret : %d\n", ret);
		if (ret == -1)
			err(EXIT_FAILURE, "kevent register");
		if (event.flags & EV_ERROR)
			errx(EXIT_FAILURE,	"Event error: %s", strerror(event.data));
	}

	map<int, string> clients; // map for client socket:data
	vector<struct kevent> change_list; // kevent vector for changelist
	struct kevent event_list[8]; // kevent array for eventlist

	/* add event for server socket */
	change_events(change_list, server_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	cout << "echo server started" << endl;

	// 통신.
	int new_events;
	struct kevent* curr_event;
	for (;;)
	{
		// kevent 호출
		new_events = kevent(kq, &change_list[0], change_list.size(), event_list, 8, NULL);
		// change_list 비우기
		change_list.clear();

		// 이벤트리스트순회
		//cout << "\nEvent list travel, nEvent : << " << new_events << "\n";
		for(int i=0;i < new_events ;i++)
		{
			curr_event = &event_list[i];
			// 해당 이벤트가 에러이벤트라면
			if (curr_event->flags & EV_ERROR)
			{
				// 서버소켓의 이벤트라면 exit
				if (curr_event->ident == server_fd)
					exit_with_perror("server socket error");
				// 클라이언트소켓 이벤트라면 disconnect
				else
				{
					cerr << "client socket[" << curr_event->ident << "] got error" << endl;
					disconnect_client(curr_event->ident, clients);
				}
			}
			// 해당 이벤트가 읽기이벤트라면
			else if (curr_event->filter == EVFILT_READ)
			{
				// 서버소켓의 이벤트라면 accept
				if (curr_event->ident == server_fd)
				{
					int client_socket;
					// 클소켓을 change_list에 읽쓰이벤트로 등록
					if ((client_socket = accept(server_fd, NULL, NULL)) == -1)
						exit_with_perror("accept error");
					cout << "client socket[" << client_socket << "] just connected" << endl;
					change_events(change_list, client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					change_events(change_list, client_socket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
					// 클라이언트의 요청저장을 위해 map에 공간할당.
					clients[client_socket] = "";
				}
				// 클소켓의 이벤트라면
				else if (clients.find(curr_event->ident) != clients.end())
				{
					char buf[1024];
					int n = read(curr_event->ident, buf, sizeof(buf));
					// read 결과가 0미만일시 disconnect
					if (n <= 0)
					{
						if (n < 0)
							cerr << "client read error!" << endl;
						disconnect_client(curr_event->ident, clients);
					}
					// 그외 데이터 저장
					else
					{
						buf[n] = '\0';
						clients[curr_event->ident] += buf;
						cout << "received data from " << curr_event->ident << ": " << clients[curr_event->ident] << endl;
					}
				}
			}
			// 해당 이벤트가 쓰기이벤트라면
			else if (curr_event->filter == EVFILT_WRITE)
			{
				map<int, string>::iterator it = clients.find(curr_event->ident);
				if (it != clients.end())
				{
					if (clients[curr_event->ident] != "") // 보낼문자열이 있을때만. -
					{
						string protocol = "HTTP/1.0 404 KO\r\n";
						string servName = "Server:simple web server\r\n";
						string cntLen = "Content-length:2048\r\n";
						string cntType = "Content-type:text/html; charset=UTF-8\r\n\r\n";
						string content = "<html><head><title>Default Page</title></head><body><h1>Hello World!</h1></body></html>";
						string response = protocol+servName+cntLen+cntType+content;
						const char *res = response.c_str();

						// 클라이언트에게 write
						int n;
						if ((n = write(curr_event->ident, res, strlen(res)) == -1))
						{
							cerr << "client write error!" << endl;
							disconnect_client(curr_event->ident, clients);
						}
						else
						{
							clients[curr_event->ident].clear();	// echo 이후 보낼 문자열을 지운다.
							cout << "http response complete" << endl;
						}
						//SendErrorMSG(curr_event->ident);
						disconnect_client(curr_event->ident, clients);
					}
				}
			}
		}
	}
}
