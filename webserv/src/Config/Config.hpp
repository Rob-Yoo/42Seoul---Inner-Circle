#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <vector>
# include <fstream>
#include <sys/_types/_size_t.h>
# include "ServerBlock.hpp"

using namespace std;

class Config {
public:
	Config(string file);

	vector<ServerBlock> &getServerBlocks(void);
private:
	Config(void);
	void	saveDirective(int idx, string line);

	ifstream			m_config_file;
	vector<ServerBlock>	m_server_blocks;
};

#endif