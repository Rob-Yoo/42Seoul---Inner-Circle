#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_pton
#define PORT 2000

// client
int main(int argc, char const *argv[])
{
	// 선언
	int sock = 0;
	struct sockaddr_in serv_addr;

	// 소켓생성
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0);
	{
		printf("Failed to Socket Init\n");
		return (1);
	}

	// 주소정보저장
	memset(serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("INVALID ADDRESS\n");
		return -1;
	}

	// 연결하기
	if (connect(sock, (struct sockaddr)))

	// read & write

	// 소켓닫기
}