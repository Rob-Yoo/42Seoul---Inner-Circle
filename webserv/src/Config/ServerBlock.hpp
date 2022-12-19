#ifndef SERVER_BLOCK_HPP
# define SERVER_BLOCK_HPP

# include <map>
# include <exception>
# include "LocationBlock.hpp"

using namespace std;

class ServerBlock {
public:
	ServerBlock(void);

	void	setPortNums(string port_nums);
	void	setServerName(string server_name);
	void	setRootDir(string root_dir);
	void	setCgiTester(string cgi_tester);
	void	setErrorPage(string error_page_info);
	void	setLocationBlock(string loc_block);
	void	setIndexFile(string file_name);

	vector<int>		getPortNum(void) const;
	string			getErrorPage(void) const;
	string			getServerName(void) const;
	string			getRootDir(void) const;
	string			getCgiTester(void) const;
	string			getCgiExtension(void) const;
	string			getIndexFile(void) const;
	map<string, LocationBlock>&	getLocationBlocks(void);
private:
	map<string, LocationBlock>	m_loc_blocks;
	string						m_error_page;
	vector<int>					m_port_nums;
	string						m_server_name;
	string						m_root_dir;
	string						m_cgi_tester;
	string						m_cgi_extension;
	string						m_index_file;
};

#endif