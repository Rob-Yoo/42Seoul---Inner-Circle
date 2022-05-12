/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:07:23 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/11 17:42:50 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *command)
{
	if (!command->is_path && !is_built_in(command->cmd))
	{
		free(command->cmd);
		command->cmd = NULL;
	}
}

char	*get_cmd_path(t_cmd *command, char **env_paths, struct stat *buf)
{
	char	*cmd_path;
	char	*tmp;

	cmd_path = NULL;
	while (*env_paths)
	{
		tmp = ft_strjoin(*env_paths, "/");
		cmd_path = ft_strjoin(tmp, command->cmd);
		free(tmp);
		tmp = NULL;
		if (stat(cmd_path, buf) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		env_paths++;
	}
	return (NULL);
}

char	*get_valid_cmd(t_cmd *command, char **env_paths)
{
	char		*cmd_path;
	struct stat	buf;

	if (stat(command->cmd, &buf) == 0)
	{
		if ((buf.st_mode & S_IFMT) == S_IFDIR)
			return (NULL);
		return (command->cmd);
	}
	else
	{
		cmd_path = get_cmd_path(command, env_paths, &buf);
		return (cmd_path);
	}
	return (NULL);
}

void	get_valid_cmd_handler(t_cmd *command, char *cmd_cpy, char **path_split)
{
	command->cmd = get_valid_cmd(command, path_split);
	if (!command->cmd)
		invalid_cmd_error(cmd_cpy);
}
