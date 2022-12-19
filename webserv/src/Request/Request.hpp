#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <utility>
# include <string>
# include <map>

# include "../Config/Config.hpp"

using namespace std;

class Request {
public:
	Request(string req_msg);
	Request(const Request& a);
	Request& operator=(const Request& a);
	~Request();

	void	setContentLength(string	content_length);
	void	setReqBody(string req_body);
	void	setReqHeader(string key, string value);
	void	setStatusCode(int status_code);
	void	setRedirectionURL(string url);
	void	setCgiPid(int cgi_pid);
	void	setCgiResult(string cgi_result);
	void	setSudoDir(string sudo_dir);
	void	setLocBlock(LocationBlock &loc_block, string url, size_t pos);
	void	setSerBlock(ServerBlock &server_block);
	void	setFilename(string file_name);
	void	setIsChunked(bool flag);

	size_t	saveOnlyBody(string &req_body);
	void	saveRequestAgain(string &req_msg);

	string				getReqHeaderValue(string key);
	string				getMethod(void) const;
	string				getReqTarget(void) const;
	string				getHttpVersion(void) const;
	string				getReqBody(void) const;
	string				getRedirectionURL(void) const;
	int					getStatusCode(void) const;
	size_t				getContentLength(void) const;
	string				getDownloadFileName(void) const;
	bool				getIsIncomplete(void) const;
	bool				getIsChunked(void) const;
	string				getIncompleteMessage(void) const;
	int					getCgiPid(void) const;
	string				getCgiResult(void) const;
	string				getSudoDir(void) const;
	string				getReqFileName(void) const;
	LocationBlock		getLocBlock(void) const;
	ServerBlock			getSerBlock(void) const;

private:
	map<string, string>	m_req_header;
	string				m_method;
	string				m_req_target;
	string				m_http_version;
	string				m_req_body;
	size_t 				m_content_length;
	bool				m_is_incomplete;
	bool				m_is_chunked;
	int					m_status_code;
	int					m_cgi_pid;
	string				m_redirection_url;
	string				m_incomplete_message;
	string				m_cgi_result;
	string				m_req_file_name;

	LocationBlock		m_loc_block;
	ServerBlock			m_ser_block;

	Request(void);

	void	saveStartLine(string start_line);
	void	saveHeader(string header_line);
	void	saveRequestFinal(void);
};


#endif
