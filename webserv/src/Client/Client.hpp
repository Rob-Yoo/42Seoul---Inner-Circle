#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "../Request/Request.hpp"
# include "../Response/Response.hpp"
# include "Cgi.hpp"
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <fcntl.h>

# define BUF_SIZE 1024	// 수정필요

class Client
{
private:
	int			fd;
	int			pipe_fd;
	sockaddr_in	addr;
	socklen_t	len;
	Cgi			*m_cgi;

	Request		*req;
	Response	*res;
	std::string	raw_request;	// HTTP 요청 원본

	bool		m_pending;

public:
	Client();
	Client(int fd, sockaddr_in addr, socklen_t len);
	~Client();
	Client(const Client& a);
	Client& operator=(const Client& a);

	int			getFd() const;
	int			getPipeFd() const;
	sockaddr_in	getAddr() const;
	socklen_t	getLen() const;
	Request		*getRequest();
	Response	*getResponse() const;
	std::string	getRawRequest() const;
	Cgi			*getCgi() const;

	void		setPipeFd(int pipe_fd);
	void		setRequest(Request *_req);
	void		setResponse(Response *_res);
	void		setRawRequest(std::string str);
	void		appendRawRequest(std::string _raw_request);
	void		setCgi(Cgi *_cgi);

	int			read_client_request();
	int			read_pipe_result();
	void		make_env(char **env);
	int			cgi_init(std::string filename);

	// HTTP METHOD
	bool		is_cgi_request(Request *req);
	int			GET(Request *req, Response *res);
	int			POST(Request *req, Response *res);
	int			DELETE(Request *req, Response *res);
};

#endif
