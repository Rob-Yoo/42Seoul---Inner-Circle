/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:58:57 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/11 17:42:59 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "../libft/libft.h"

# define READ 0
# define WRITE 1

# define TRUE 1
# define FALSE 0

# define WAIT_TIMEOUT 258

# define ERROR -1
# define SUCCESS 1

# define SEPARATOR 1
# define REDIR_L 2
# define REDIR_R 3
# define REDIR_RR 4
# define HEREDOC 5
# define PIPE_TYPE 6
# define ERROR_TYPE 7

typedef struct s_state
{
	char	**envp;
	int		exit_status;
}	t_state;

typedef struct s_redir {
	int				type;
	char			*file_name;
	struct s_redir	*next;
	struct s_redir	*prev;
}	t_redir;

typedef struct s_cmd {
	int				is_pipe;
	int				is_path;
	int				pipe[2];
	char			*cmd;
	char			**argv;
	int				argc;
	struct s_redir	*input;
	struct s_redir	*output;
	char			*here_filename;
	char			*heredoc;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

/*global*/
t_state	g_state;

/*builtins*/
void	ft_cd(t_cmd *command);
void	ft_pwd(void);
void	ft_env(void);
void	ft_echo(t_cmd *command);
void	ft_exit(t_cmd *command);
void	ft_unset(t_cmd *command);
void	ft_export(t_cmd *command);
int		is_built_in(char *cmd);
int		exec_built_in(t_cmd *command, int flag);
int		exec_built_in_hanlder(t_cmd *command);
void	print_envp(void);
void	set_new_env(char *key, char *new_value);
char	*get_new_value(char *key, char *argv);
/*parser*/
char	**ft_split_cmds(char *str);
char	**parse_cmds(char **commands);
void	set_is_path(t_cmd *cmd);
void	change_quote(char c, char *flag);
int		handle_heredoc(t_cmd *cur, char *heredoc, int *i);
int		_redir(t_cmd *cur, char **commands, int *i);
void	set_cmd_list(char **commands, t_cmd	*cur, int i, int i_argv);
void	make_file(char *filename);
void	ft_free_two_ptr(char **ptr);
void	parser(char **input, t_cmd **head);

/*env*/
void	copy_env(char **envp);
void	join_env(char **temp, char *key);
char	*get_env(char *key);
char	*get_env_key(char *command, int start);
int		get_env_index(char *key);
int		parse_env(char **temp, char *command, int start);
void	update_env(char *key, char *new_value);

void	init_signal(void);
void	handle_signal(int signo);
int		is_valid_env_key(char *str);
int		ft_twoptr_len(char **twoptr);
int		count_pipe(char **commands);
void	ft_strjoin_char(char **dst, char ch);

//error.c
int		error_cmds(t_cmd *node);
void	ft_error(void);
int		invalid_cmd_error(char *cmd);

// redirection
int		rdr_l(t_redir *redir);
int		rdr_r(t_redir *redir);
int		rdr_rr(t_redir *redir);
int		rdr_l_error(char *file_name);
int		redirection_handler(t_cmd *command);

// execute
int		execute_cmds(t_cmd *command);
char	*get_valid_cmd(t_cmd *command, char **env_paths);

/*cmd list*/
int		here_filename(t_cmd *head);
t_cmd	*create_cmd_node(t_cmd *prev);
void	delete_cmd_list(t_cmd **cmd);
void	malloc_cmd_list(char **commands, t_cmd **head);

/*redir list*/
t_redir	*create_redir_node(int type, char *file_name);
void	delete_redir_list(t_redir *redir);
void	add_redir_node(t_redir *new_node, t_redir *head);
int		handle_redir(t_cmd *node, int type, char *file_name, int *i);

//pipe.c
int		use_pipe(t_cmd *command, int *pipe_open);

void	free_env_path(char **path);
char	*get_cmd_path(t_cmd *command, char **env_paths, struct stat *buf);
void	get_valid_cmd_handler(t_cmd *command, char *cmd_cpy, char **path_split);
void	free_cmd(t_cmd *command);
#endif
