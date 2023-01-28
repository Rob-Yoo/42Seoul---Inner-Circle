#ifndef CGI_HPP
# define CGI_HPP

# include "../Request/Request.hpp"
# include "../Response/Response.hpp"
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <fcntl.h>

class Cgi
{
private:
	int			to_child[2];
	int			to_parent[2];
	char		**env;
	std::string	input;
	std::string	output;

	void	make_env(char **env);

public:
	Cgi(char **_env);
	~Cgi();

	int *getToChild(void);
	int *getToParent(void);
	char **getEnv(void);
	std::string getInput(void) const;
	std::string getOutput(void) const;
	void setInput(std::string input);
	void setOutput(std::string output);
};

#endif
