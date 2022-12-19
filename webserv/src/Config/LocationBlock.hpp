#ifndef LOCATION_BLOCK_HPP
# define LOCATION_BLOCK_HPP

#include <cstddef>
# include <iostream>
# include <string>
# include <vector>

using namespace std;

class LocationBlock {
public:
	LocationBlock(void);
	LocationBlock(string root_dir, string index_file, string error_page);

	void	setValidMethod(string loc_block, size_t pos);
	void	setDefaultMethod(string method);
	void	setMaxBodySize(string loc_block, size_t pos);
	void	setUploadDirectory(string loc_block, size_t pos);
	void	setRootDir(string loc_block, size_t pos);
	void	setAutoIndex(string loc_block, size_t pos);
	void	setRedirectionURL(string loc_block, size_t pos);
	void	setIndexFile(string loc_block, size_t pos);

	vector<string>	getValidMethod(void) const;
	string			getUploadDirectory(void) const;
	string			getRootDir(void) const;
	size_t 			getMaxBodySize(void) const;
	bool			getAutoIndex(void) const;
	string			getRedirectionURL(void) const;
	string			getIndexFile(void) const;
	string			getErrorPage(void) const;
private:
	vector<string>	m_valid_method;
	size_t			m_max_body_size;
	string			m_upload_dir;
	string			m_root_dir;
	string			m_index_file;
	string			m_error_page;
	bool			m_autoindex;
	string			m_redirection_url;
};

#endif
