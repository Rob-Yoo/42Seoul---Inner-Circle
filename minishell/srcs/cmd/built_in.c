/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:32:07 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/08 17:21:08 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 5) || !ft_strncmp("pwd", cmd, 4) || \
	!ft_strncmp("export", cmd, 6) || !ft_strncmp("unset", cmd, 6) || \
	!ft_strncmp("env", cmd, 4) || !ft_strncmp("exit", cmd, 5) || \
	!ft_strncmp("cd", cmd, 3))
		return (TRUE);
	return (FALSE);
}

int	exec_built_in_hanlder(t_cmd *command)
{
	int	w_fd;
	int	r_fd;

	if (command->input || command->output)
	{
		w_fd = dup(WRITE);
		r_fd = dup(READ);
		if (w_fd == ERROR || r_fd == ERROR)
			return (ERROR);
		if (redirection_handler(command) == ERROR)
			return (ERROR);
	}
	exec_built_in(command, FALSE);
	if (command->input)
	{
		if (dup2(r_fd, READ) == ERROR)
			return (ERROR);
	}
	if (command->output)
	{
		if (dup2(w_fd, WRITE) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	exec_built_in(t_cmd *command, int flag)
{
	if (!ft_strncmp(command->cmd, "echo", ft_strlen(command->cmd) + 1))
		ft_echo(command);
	else if (!ft_strncmp(command->cmd, "cd", ft_strlen(command->cmd) + 1))
		ft_cd(command);
	else if (!ft_strncmp(command->cmd, "env", ft_strlen(command->cmd) + 1))
		ft_env();
	else if (!ft_strncmp(command->cmd, "pwd", ft_strlen(command->cmd) + 1))
		ft_pwd();
	else if (!ft_strncmp(command->cmd, "exit", ft_strlen(command->cmd) + 1))
		ft_exit(command);
	else if (!ft_strncmp(command->cmd, "unset", ft_strlen(command->cmd) + 1))
		ft_unset(command);
	else if (!ft_strncmp(command->cmd, "export", ft_strlen(command->cmd) + 1))
		ft_export(command);
	if (flag)
		exit(0);
	return (SUCCESS);
}
