#include "LocationBlock.hpp"
#include <atomic>
#include <iterator>
#include <string>

LocationBlock::LocationBlock() {}

LocationBlock::LocationBlock(string root_dir, string index_file, string error_page)
: m_max_body_size(1024 * 1024), m_upload_dir(""), m_autoindex(false), m_redirection_url("")
{
	this->m_root_dir = root_dir;
	this->m_index_file = index_file;
	this->m_error_page = error_page;
}

void LocationBlock::setValidMethod(string loc_block, size_t pos)
{
	string	l_e = "limit_except";
	string	method = "";
	size_t	len = l_e.length();
	bool	flag = false;

	for (size_t i = pos + len + 1;loc_block[i] != ';';i++)
	{
		if (loc_block[i] != ' ')
			method += loc_block[i];
		else
			flag = true;
		if (flag || loc_block[i + 1] == ';')
		{
			this->m_valid_method.push_back(method);
			method = "";
			flag = false;
		}
	}
}

void	LocationBlock::setMaxBodySize(string loc_block, size_t pos)
{
	string		max_body_size = "";
	string		l_e = "client_max_body_size";
	size_t		len = l_e.length();
	int			flag = -1;

	for (size_t i = pos + len + 1;loc_block[i] != ';';i++)
	{
		if (loc_block[i] == 'k' || loc_block[i] == 'K')
			flag = 0;
		else if (loc_block[i] == 'm' || loc_block[i] == 'M')
			flag = 1;
		else if (loc_block[i] == 'g' || loc_block[i] == 'G')
			flag = 2;
		else if (loc_block[i + 1] == ';')
		{
			max_body_size += loc_block[i];
			if (!max_body_size.empty())
				flag = 3;
			break;
		}
		max_body_size += loc_block[i];
	}
	if (flag == -1)
	{
		cerr << "Invalid client_max_body_size\n";
		exit(1);
	}
	else if (flag == 0)
		this->m_max_body_size = stoll(max_body_size) * 1024;
	else if (flag == 1)
		this->m_max_body_size = stoll(max_body_size) * 1024 * 1024;
	else if (flag == 2)
		this->m_max_body_size = stoll(max_body_size) * 1024 * 1024 * 1024;
	else if (flag == 3)
		this->m_max_body_size = stoll(max_body_size);
}

void LocationBlock::setUploadDirectory(string loc_block, size_t pos)
{
	string	l_e = "upload";
	size_t	len = l_e.length();

	for (size_t i = pos + len + 1;loc_block[i] != ';';i++)
		this->m_upload_dir += loc_block[i];
}

void LocationBlock::setRootDir(string loc_block, size_t pos)
{
	string	l_e = "root";
	size_t	len = l_e.length();

	this->m_root_dir += "/";
	for (size_t i = pos + len + 1;loc_block[i] != ';';i++)
		this->m_root_dir += loc_block[i];
}

void LocationBlock::setIndexFile(string loc_block, size_t pos)
{
	string	l_e = "index";
	size_t	len = l_e.length();

	this->m_index_file = "";
	for (size_t i = pos + len + 1;loc_block[i] != ';';i++)
		this->m_index_file += loc_block[i];
}

void LocationBlock::setRedirectionURL(string loc_block, size_t pos)
{
	string	l_e = "return";
	size_t	len = l_e.length();

	for (size_t i = pos + len + 1;loc_block[i] != ';';i++)
		this->m_redirection_url += loc_block[i];
}

void LocationBlock::setAutoIndex(string loc_block, size_t pos)
{
	string	l_e = "autoindex";
	size_t	len = l_e.length();
	string	on_off = "";

	for (size_t i = pos + len + 1;loc_block[i] != ';';i++)
		on_off += loc_block[i];
	if (on_off != "off" && on_off != "on")
	{
		cerr << "Invalid Config File\n";
		exit(1);
	}
	if (on_off == "on")
		this->m_autoindex = true;
}

void	LocationBlock::setDefaultMethod(string method) { this->m_valid_method.push_back(method); }

vector<string>	LocationBlock::getValidMethod(void) const {
	return this->m_valid_method;
}

size_t	LocationBlock::getMaxBodySize(void) const {
	return this->m_max_body_size;
}

string	LocationBlock::getUploadDirectory(void) const {
	return this->m_upload_dir;
}

// "/" 안붙어있음
string	LocationBlock::getRootDir(void) const {
	return this->m_root_dir;
}

bool	LocationBlock::getAutoIndex(void) const {
	return this->m_autoindex;
}

string	LocationBlock::getRedirectionURL(void) const {
	return this->m_redirection_url;
}

string	LocationBlock::getIndexFile(void) const {
	return this->m_index_file;
}

string	LocationBlock::getErrorPage(void) const {
	return this->m_error_page;
}
