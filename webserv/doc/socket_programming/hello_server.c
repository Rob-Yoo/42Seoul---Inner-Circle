#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clent_addr_size;

	char message[] = "Hello World!";

	if (argc != 2)
	{
		printf("usage : %s <port>\n", argv[0]);
		exit(1);
	}

	//serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("Socket() error");

	printf("[DEBUG] socket fd : %d\n", serv_sock);
	// memset(&serv_addr, 0, sizeof(serv_addr));
	// serv_addr
}

void error_handling(char *message)
{
	printf("%s\n", message);
	exit(1);
}