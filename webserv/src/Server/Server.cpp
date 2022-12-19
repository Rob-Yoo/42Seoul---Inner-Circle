/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:50:39 by gshim             #+#    #+#             */
/*   Updated: 2022/11/14 20:01:42 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//=============================================================================
//	Orthodox Canonical Form
//=============================================================================
Server::Server()
{
}
Server::Server(string config_filepath)
{
	// read config file.
	config = new Config(config_filepath);
}

//=============================================================================
//	Method
//=============================================================================
int Server::init_socket(int port)
{
	// 소켓 생성
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}
	printf("Open new Listening socket : %d on port %d\n", server_fd, port);

	// 주소 구조체에 서버의 IP,PORT 저장
	memset(address.sin_zero, 0, sizeof(address.sin_zero));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( port );

	// Bind
	if (bind(server_fd, (struct sockaddr *)&address, (socklen_t)sizeof(address)) < 0)
	{
		perror("In bind");
		exit(EXIT_FAILURE);
	}
	fd_to_port[server_fd] = port;

	// Listen
	if (listen(server_fd, 10) < 0)
	{
		perror("In listen");
		exit(EXIT_FAILURE);
	}

	return (0);
}

// server_fd
int Server::init_multiplexing()
{
	struct kevent event;	 /* 감시대상 이벤트 */
	int flags = 0;
	int ret = 0;

	kq_fd = kqueue();
	if (kq_fd == -1)
		err(EXIT_FAILURE, "kqueue() failed");

	{
		vector<ServerBlock> v = getConfig()->getServerBlocks(); // reference로 받으면 좋을듯...!
		for(size_t i=0;i<v.size();i++)
		{
			vector<int> ports = v[i].getPortNum();
			for(size_t j=0;j<ports.size();j++)
			{
				int curr_port = ports[j];
				// already registered port
				if (serverblock_info.find(curr_port) != serverblock_info.end())
				{
					vector<ServerBlock> &blocks = serverblock_info[curr_port];
					int flag = 0;
					for(size_t k=0;k<blocks.size();k++)
					{
						if (blocks[k].getServerName() == v[i].getServerName())
						{
							flag = 1;
							break;
						}
					}
					if (!flag)
						blocks.push_back(v[i]);
				}
				// open listen socket
				// init_socket의 반환값을 EV_SET인자로 넣는 방식이 좋아보인다.
				else
				{
					init_socket(curr_port); // 포트열기
					// 포트에 해당하는 fd를 kqueue에 SET하기
					EV_SET(&event, server_fd, EVFILT_READ, EV_ADD | EV_CLEAR, flags, 0,	NULL);
					change_events(server_fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					serverblock_info[curr_port].push_back(v[i]);
				}
			}
		}
	}

	ret = kevent(kq_fd, &event, 1, NULL, 0, NULL);
	if (ret == -1)
		err(EXIT_FAILURE, "kevent register");
	if (event.flags & EV_ERROR)
		errx(EXIT_FAILURE,	"Event error: %s", strerror(event.data));
	return (0);
}

int Server::run()
{
	printf("[DEBUG] serverblock_info : \n");
	for (map<int, vector<ServerBlock> >::iterator iter = serverblock_info.begin() ; iter !=  serverblock_info.end(); iter++)
	{
		cout << iter->first << ":" << endl;
		for(size_t i=0;i<iter->second.size();i++)
			cout <<  "	[" << iter->second[i].getServerName() << "]" << endl;
	}
	cout << endl;

	std::cout << "WebServer started" << std::endl;

	int new_events;
	struct kevent* curr_event;
	for (;;)
	{
		// kevent 호출
		new_events = kevent(kq_fd, &change_list[0], change_list.size(), event_list, 8, NULL);
		// change_list 비우기
		change_list.clear();
		// 이벤트리스트순회
		for(int i=0;i < new_events ;i++)
		{
			curr_event = &event_list[i];

			if (curr_event->flags & EV_ERROR)
				callback_error(curr_event->ident);
			else if (curr_event->filter == EVFILT_READ)
				callback_read(curr_event->ident, curr_event->data);
			else if (curr_event->filter == EVFILT_WRITE)
				callback_write(curr_event->ident, curr_event->data);
		}
	}
}

map<string, LocationBlock>::iterator	Server::locationBlockMapping(Client *cli, ServerBlock &s_b)
{
	string url = cli->getRequest()->getReqTarget();
	map<string, LocationBlock>::iterator	it;
	map<string, LocationBlock>::iterator	matching_it;
	size_t	matched_len = 0;

	cli->getRequest()->setSerBlock(s_b);
	it = s_b.getLocationBlocks().begin();
	matching_it = s_b.getLocationBlocks().end();
	// URL과 로케이션 블록의 Longest Prefix Matching
	for (it = s_b.getLocationBlocks().begin();it != s_b.getLocationBlocks().end();it++)
	{
		if (url == it->first)
		{
			matching_it = it;
			break;
		}
		else if (it->first == "/")
		{
			matching_it = it;
			matched_len = 1;
			continue;
		}
		size_t	find = url.find(it->first);
		if (find == 0)
		{
			if (matched_len < it->first.length() && url[it->first.length()] == '/')
			{
				matched_len = it->first.length();
				matching_it = it;
			}
		}
	}
	return matching_it;
}

// 여기서 걸러진 요청은 바로 write할 수 있게 바꿔야 한다.
int	Server::execute_client_request(int client_fd)
{
	Client *cli = clients_info[client_fd];
	ServerBlock s_b = find_serverblock(client_fd);
	if (cli->getRequest()->getStatusCode() != 0)
	{
		cout << "Status Code : " << cli->getRequest()->getStatusCode() << endl;
		return 1;
	}
	map<string, LocationBlock>::iterator matching_it = locationBlockMapping(cli, s_b);
	bool is_valid_method = false;

	if (matching_it != s_b.getLocationBlocks().end())
	{
		cli->getRequest()->setLocBlock(matching_it->second, cli->getRequest()->getReqTarget(), matching_it->first.length());
		vector<string>	valid_method = matching_it->second.getValidMethod();
		if (valid_method.size() == 0)
		{
			matching_it->second.setDefaultMethod("GET");
			matching_it->second.setDefaultMethod("POST");
			matching_it->second.setDefaultMethod("DELETE");
		}
		valid_method = matching_it->second.getValidMethod();
		for (size_t i = 0; i < valid_method.size();i++)
		{
			if (valid_method[i] == cli->getRequest()->getMethod() || cli->getRequest()->getMethod() == "PUT")
			{
				is_valid_method = true;

				// Rootdir 확인
				cout << "this location's block's root is...  ";
				cout << cli->getRequest()->getLocBlock().getRootDir() << endl;
				cout << "this location's block's index is...  ";
				cout << cli->getRequest()->getLocBlock().getIndexFile() << endl;
				break;
			}
		}
		if (is_valid_method)
		{
			if (cli->getRequest()->getContentLength() <= matching_it->second.getMaxBodySize() || \
			matching_it->second.getMaxBodySize() == 0)
			{
				if (matching_it->second.getRedirectionURL() == "")
					cli->getRequest()->setStatusCode(0); // not define yet.
				else
				{
					cli->getRequest()->setRedirectionURL(matching_it->second.getRedirectionURL());
					cli->getRequest()->setStatusCode(301);
				};
			}
			else
				cli->getRequest()->setStatusCode(413); // Body Size Too Large
		}
		else
			cli->getRequest()->setStatusCode(405); // Invalid Method
	}
	else
		cli->getRequest()->setStatusCode(404); // Not Found
	// status code 디버깅용
	cout << "Status Code : " << cli->getRequest()->getStatusCode() << endl;
	return 1;
}

ServerBlock Server::find_serverblock(int client_fd)
{
	Client *cli = clients_info[client_fd];

	// Client의 request정보를 통해 어떤 서버블록을 사용할지 정한다.
	std::string host_header = cli->getRequest()->getReqHeaderValue("Host");
	std::string hostname = "", port = "";

	// 헤더 정보 저장
	for(size_t i=0;i<host_header.length();i++)
	{
		if (host_header[i] == ':')
		{
			hostname = host_header.substr(0, i);
			port = host_header.substr(i + 1);
			break;
		}
	}
	// 서버 블록 결정
	std::vector<ServerBlock> v;
	if (hostname == "" || port == "")
	{
		ServerBlock mock;
		cli->getRequest()->setStatusCode(400);
		return mock;
	}
	if (serverblock_info.find(stoi(port)) != serverblock_info.end())
		v = serverblock_info[stoi(port)];
	else
	{
		std::cout << "Default ServerBlock choose..." << std::endl;
		return v[0];
	}
	int flag = false;
	ServerBlock s_b;
	for(size_t i=0;i<v.size();i++)
	{
		if (v[i].getServerName() == hostname)
		{
			s_b = v[i];
			flag = true;
			break;
		}
	}
	if (!flag)
		s_b = v[0];

	return s_b;
}

//=============================================================================
//	Getter & Setter
//=============================================================================

Config*	Server::getConfig(void) const { return config; }
