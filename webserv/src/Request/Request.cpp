#include "Request.hpp"

Request::Request() {}

Request::Request(const Request& a)
{
	*this = a;
}

Request& Request::operator=(const Request& a)
{
	m_req_header = a.m_req_header;
	m_http_version = a.m_http_version;
	m_method = a.m_method;
	m_req_body = a.m_req_body;
	m_req_target = a.m_req_target;

	return *this;
}

Request::~Request(){}


Request::Request(string req_msg): m_req_header(), m_method(""), m_req_target(""), m_http_version(""), m_req_body(""), m_content_length(0), m_is_incomplete(false), m_is_chunked(false), m_status_code(0), m_cgi_pid(-1)
{
	string	line = "";
	size_t	len = req_msg.length();
	bool	crlf_complete = true;

	for (size_t i = 0;req_msg[i];i++)
	{
		if (req_msg[i] == '\r')
		{
			crlf_complete = false;
			if (m_method.empty())
				this->saveStartLine(line);
			else if (line.length() == 0)
			{
				if (i + 2 < len)
				{
					line = req_msg.substr(i + 2);
					this->setReqBody(line);
				}
				return ;
			}
			else
				this->saveHeader(line);
			line = "";
		}
		else if (req_msg[i] != '\n')
			line += req_msg[i];
		else if (req_msg[i] == '\n')
			crlf_complete = true;
	}
	if (line.length() != 0 || !crlf_complete)
	{
		this->m_incomplete_message = line;
		this->m_is_incomplete = true;
	}
}

void	Request::saveRequestAgain(string &req_msg)
{
	string	line = "";
	size_t	len = req_msg.length();
	bool	crlf_complete = true;

	for (size_t i = 0;req_msg[i];i++)
	{
		if (req_msg[i] == '\r')
		{
			crlf_complete = false;
			if (m_method.empty())
				this->saveStartLine(line);
			else if (line.length() == 0)
			{
				if (i + 2 < len)
				{
					line = req_msg.substr(i + 2);
					line = req_msg.substr(i);
					this->setReqBody(line);
					this->m_is_incomplete = false;
				}
				return ;
			}
			else
				this->saveHeader(line);
			line = "";
		}
		else if (req_msg[i] != '\n')
			line += req_msg[i];
		else if (req_msg[i] == '\n')
			crlf_complete = true;
	}
	if (line.length() != 0 || !crlf_complete)
		this->m_incomplete_message = line;
	else
		this->m_is_incomplete = false;
}

size_t	Request::saveOnlyBody(string &req_body)
{
	this->m_req_body.append(req_body);
	return req_body.length();
}

void	Request::saveStartLine(string start_line)
{
	int		cnt = 0;

	for (size_t i = 0;i < start_line.length();i++)
	{
		if (start_line[i] != ' ')
		{
			if (cnt == 0)
				this->m_method += start_line[i];
			else if (cnt == 1)
				this->m_req_target += start_line[i];
			else
				this->m_http_version += start_line[i];
		}
		else
			cnt++;
	}
}

void	Request::saveHeader(string header_line)
{
	string	key = "";
	string	value = "";

	for(size_t i = 0;i<header_line.length();i++)
	{
		if (header_line[i] != ':')
			continue ;
		if (header_line[i + 1] == ' ')
			this->setReqHeader(header_line.substr(0, i), header_line.substr(i+2));
		else
			this->setReqHeader(header_line.substr(0, i), header_line.substr(i+1));
		break;
	}
}

// ----------------------------------------- Setter -----------------------------------------------------
void	Request::setReqHeader(string key, string value)
{
	if (key == "Content-Length" || key == "content-length")
		setContentLength(value);
	if ((key == "Transfer-Encoding" || key == "transfer-encoding") && value == "chunked")
		setIsChunked(true);
	this->m_req_header.insert(pair<string, string>(key, value));
}

void	Request::setLocBlock(LocationBlock &loc_block, string url, size_t pos)
{
	string	split_url = "";

	this->m_loc_block = loc_block;
	if (url[pos] == '/')
		split_url = url.substr(pos + 1);
	else
		split_url = url.substr(pos);
	if (!split_url.empty() && split_url.back() == '/')
		split_url.pop_back();
	this->m_req_file_name += split_url;
}

void	Request::setContentLength(string content_length) { this->m_content_length = stoll(content_length); }

void	Request::setCgiPid(int cgi_pid) { this->m_cgi_pid = cgi_pid; }

void	Request::setCgiResult(string cgi_result) { this->m_cgi_result = cgi_result; }

void	Request::setStatusCode(int status_code) {this->m_status_code = status_code; }

void	Request::setReqBody(string body) { this->m_req_body = body; }

void	Request::setRedirectionURL(string url) { this->m_redirection_url = url; }

void	Request::setSerBlock(ServerBlock &server_block) { this->m_ser_block = server_block; }

void	Request::setIsChunked(bool flag) { this->m_is_chunked = flag; }

// ----------------------------------------- Getter -----------------------------------------------------
string	Request::getReqHeaderValue(string key) {
	string	lower_key = "";
	for (size_t i = 0;i < key.length();i++)
		lower_key += tolower(key[i]);
	if (this->m_req_header.find(key) != this->m_req_header.end())
		return this->m_req_header[key];
	if (this->m_req_header.find(lower_key) != this->m_req_header.end())
		return this->m_req_header[lower_key];
	return "";
}

size_t	Request::getContentLength(void) const { return this->m_content_length; }

string	Request::getReqBody(void) const { return this->m_req_body; }

string	Request::getMethod(void) const { return this->m_method; }

string	Request::getReqTarget(void) const { return this->m_req_target; }

string	Request::getHttpVersion(void) const { return this->m_http_version; }

string	Request::getRedirectionURL(void) const { return this->m_redirection_url; }

int		Request::getStatusCode(void) const { return this->m_status_code; }

bool	Request::getIsIncomplete(void) const { return this->m_is_incomplete; }

bool	Request::getIsChunked(void) const { return this->m_is_chunked; }

string	Request::getIncompleteMessage(void) const { return this->m_incomplete_message; }

int		Request::getCgiPid(void) const { return m_cgi_pid; }

string	Request::getCgiResult(void) const { return m_cgi_result; }

string	Request::getReqFileName(void) const { return this->m_req_file_name; }

LocationBlock	Request::getLocBlock(void) const { return this->m_loc_block; }

ServerBlock		Request::getSerBlock(void) const { return this->m_ser_block; }
