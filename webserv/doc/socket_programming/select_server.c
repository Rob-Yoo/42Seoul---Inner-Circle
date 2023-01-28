#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_pton
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>

#ifndef BUF_SIZE
# define BUF_SIZE 100
#endif
// #ifndef PORT
// # define PORT 2000
// #endif

int main(int argc, char *argv[])
{
	int serv_socket, clnt_socket;
	struct sockaddr_in address, clnt_adr;
	int addrlen = sizeof(address);

	fd_set reads, temps;
	int str_len, fd_max, fd_num;
	char buf[BUF_SIZE];
	struct timeval timeout;

	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(0);
	}
	printf("Open Server on %s!\n", argv[1]);
	// 소켓 생성
	if ((serv_socket = socket(PF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}

	// 주소 구조체에 서버의 IP,PORT 저장
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(atoi(argv[1]));

	// Bind
	if (bind(serv_socket, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("In bind");
		exit(EXIT_FAILURE);
	}
	// Listen
	if (listen(serv_socket, 5) < 0)
	{
		perror("In listen");
		exit(EXIT_FAILURE);
	}

	FD_ZERO(&reads);
	FD_SET(serv_socket, &reads);	// 표준입력 fd0을 관찰대상으로 추가한다.
	fd_max = serv_socket;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	while (1)
	{
		temps = reads;
		// timeout.tv_sec = 5;
		// timeout.tv_usec = 0;
		printf("Debug...\n");
		if ((fd_num = select(fd_max + 1, &temps, 0, 0, &timeout)) == -1)
			break ;
		if (fd_num == 0)
			continue ;

		printf("Event occured, fd_num = %d\n", fd_num);

		// 모든 감시대상중
		for(int i=0;i<fd_max+1;i++)
		{
			// 이벤트발생대상을 모두 찾았다면 탐색중지
			if (fd_num == 0)
				break;
			// 변화없는 대상은 넘어간다.
			if(!FD_ISSET(i, &temps))
				continue ;

			// 서버소켓 이벤트의 경우
			if (i == serv_socket)
			{
				printf("Listening socket event\n");
				if ((clnt_socket = accept(serv_socket, (struct sockaddr *)&clnt_adr, (socklen_t*)&addrlen))<0)
					exit(EXIT_FAILURE);
				if (fd_max < clnt_socket)
					fd_max = clnt_socket;
				FD_SET(clnt_socket, &reads);	// 감시대상에 추가
			}
			// 이미 연결된 클라이언트에서의 이벤트의 경우
			else
			{
				printf("connected socket event\n");
				int len = read( clnt_socket , buf, 30000);
				if (len == 0)
				{
					FD_CLR(i, &reads);
					close(i);
					printf("closed client: %d \n", i);
				}
				else
					//write(i, buf, str_len);
					printf("client[%d] : %s\n", i, buf);
			}
		}
	}
	close(serv_socket);
	return (0);
}