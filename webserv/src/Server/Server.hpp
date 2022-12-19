#ifndef Server_HPP
# define Server_HPP

# include "../Client/Client.hpp"
# include "../Config/Config.hpp"
# include <iostream>
# include <utility>
# include <string>
# include <map>
# include <vector>

# include <sys/socket.h>
# include <unistd.h>
# include <netinet/in.h>
# include <sys/event.h>
#include <sys/_types/_size_t.h>
# include <err.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define DELETE_HTTP_METHOD "DELETE"
# define AUTOINDEX_URL "/autoindex"
# define DOWNLOAD_URL "/download"

class Server {

private:
	std::map<int, Client*>	clients_info;
	std::map<int, int>		pipe_to_client;
	std::map<int, int>		file_to_client;

	Config					*config;

	// for socket
	int server_fd;
	struct sockaddr_in address;
	int addrlen;

	// for kqueue
	int kq_fd;
	std::vector<struct kevent> change_list;		// kevent vector for changelist
	struct kevent event_list[8];			// kevent array for eventlist

public:
	// fd, port
	map<int, int> fd_to_port;
	// port, serverblock
	map<int, vector<ServerBlock> > serverblock_info; // ㄴㅏ주ㅇ에 private옮기고 getter/setter

//=============================================================================
//	Orthodox Canonical Form
//=============================================================================
	Server();							// 기본생성자
	Server(string config_filepath);		// 생성자

//=============================================================================
//	Method
//=============================================================================
	int init_socket(int port);
	int init_multiplexing();
	int run();

	int callback_error(int fd);
	int callback_read(int fd, intptr_t datalen);
	int callback_write(int fd, intptr_t datalen);

	void exit_with_perror(const string& msg);
	void disconnect_pipe(int pipe_fd);
	void disconnect_client(int client_fd);
	void change_events(uintptr_t ident, int16_t filter,
		uint16_t flags, uint32_t fflags, intptr_t data, void *udata);


	int connect_new_client(int fd);
	int read_client_request();
	int	execute_client_request(int client_fd);
	int read_pipe_result();

	ServerBlock find_serverblock(int client_fd);
	map<string, LocationBlock>::iterator locationBlockMapping(Client *cli, ServerBlock &s_b);

	int	client_read(int fd);
	int	pipe_read(int fd);
	int	file_read(int fd, intptr_t datalen);
	int	client_write(int fd);
	int	pipe_write(int fd);
	int	file_write(int fd, intptr_t datalen);

//=============================================================================
//	Getter & Setter
//=============================================================================
	Config	*getConfig(void) const;

//=============================================================================
//	Condition method
//=============================================================================
	int	is_listensocket(int fd);
	int	is_client(int fd);
	int	is_pipe(int fd);
	int	is_file(int fd);
};

#endif
