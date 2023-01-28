#include "Config.hpp"
#include <sys/_types/_size_t.h>

Config::Config(void) {}

Config::Config(string file) {
	string	line = "";
	string	loc_block = "";
	bool	loc_block_flag = false;
	int		idx = -1;

	this->m_config_file.open(file);
	if (this->m_config_file.fail())
	{
		cerr << "Error\n";
		exit(1);
	}
	while (getline(this->m_config_file, line))
	{
		if (line == "server {")
		{
			this->m_server_blocks.push_back(ServerBlock());
			idx++;
		}
		else if (!line.empty() && line != "}")
		{
			if (line.find("location") != string::npos)
				loc_block_flag = true;
			if (loc_block_flag)
			{
				loc_block += line;
				if (line == "\t}")
					loc_block_flag = false;
				if (!loc_block_flag)
				{
					this->m_server_blocks[idx].setLocationBlock(loc_block);
					loc_block = "";
				}
				loc_block += "\n";
			}
			else
				this->saveDirective(idx, line);
		}
	}
}

void	Config::saveDirective(int idx, string line)
{
	string	directive = "";
	string	dir_data = "";
	bool	flag = true;

	if (line.back() != ';')
	{
		cerr << "Sentence Must Be Finished By ';'\n";
		exit(1);
	}
	for (size_t i = 1; i < line.length() - 1;i++)
	{
		if (line[i] == ' ' && flag)
		{
			flag = false;
			continue;
		}
		if (flag)
			directive += line[i];
		else
			dir_data += line[i];
	}
	if (directive == "listen")
		this->m_server_blocks[idx].setPortNums(dir_data);
	else if (directive == "server_name")
		this->m_server_blocks[idx].setServerName(dir_data);
	else if (directive == "root")
		this->m_server_blocks[idx].setRootDir(dir_data);
	else if (directive == "cgi")
		this->m_server_blocks[idx].setCgiTester(dir_data);
	else if (directive == "error_page")
		this->m_server_blocks[idx].setErrorPage(dir_data);
	else if (directive == "index")
		this->m_server_blocks[idx].setIndexFile(dir_data);
}

vector<ServerBlock> &Config::getServerBlocks(void)
{
	return this->m_server_blocks;
}
