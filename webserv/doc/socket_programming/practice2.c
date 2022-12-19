#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_pton

int main(int argc, char *argv[])
{
	int serv_fd, addrlen = sizeof(serv_addr);
	struct sockaddr_in serv_addr;
	serv_fd = socket(PF_INET, SOCK_STREAM, 0);

	memset(serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
	bind(serv_fd, (struct sockaddr *)&serv_addr, (socklen_t)addrlen);
	listen(serv_fd, 5);

	int newclient;
	newclient = accept(serv_fd, (struct sockaddr *)&serv_addr, (socklen_t*)&addrlen);
}