/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:55:40 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/11 17:45:36 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	child_handler(t_cmd *command, int flag)
{
	signal(SIGQUIT, SIG_DFL);
	if (command->input || command->output)
	{
		if (redirection_handler(command) == ERROR)
			return (ERROR);
	}
	if (command->is_pipe && !command->output)
	{
		if (dup2(command->pipe[WRITE], WRITE) == ERROR)
			return (ERROR);
	}
	if (command->prev && command->prev->is_pipe && !command->input)
	{
		if (dup2(command->prev->pipe[READ], READ) == ERROR)
			return (ERROR);
	}
	if (flag)
		exec_built_in(command, flag);
	else
	{
		if (execve(command->cmd, command->argv, g_state.envp) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

void	parent_handler(t_cmd *command, pid_t pid, int pipe_open)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (status == SIGINT)
		printf("\n");
	else if (status == SIGQUIT)
		printf("Quit: %d\n", status);
	if (pipe_open)
	{
		close(command->pipe[WRITE]);
		if (!command->next)
			close(command->pipe[READ]);
	}
	if (command->prev && command->prev->is_pipe)
		close(command->prev->pipe[READ]);
	init_signal();
	g_state.exit_status = *(int *)&status >> 8 & 0x000000ff;
}

static int	exec_cmd(t_cmd *command, int flag)
{
	pid_t	pid;
	int		pipe_open;

	if (use_pipe(command, &pipe_open) == ERROR)
		return (ERROR);
	if (flag && !pipe_open)
	{
		if (exec_built_in_hanlder(command) == ERROR)
			return (ERROR);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (ERROR);
		else if (!pid)
		{
			if (child_handler(command, flag) == ERROR)
				exit(1);
		}
		else
			parent_handler(command, pid, pipe_open);
	}
	return (SUCCESS);
}

int	execute_cmds(t_cmd *command)
{
	char	*path;
	char	**path_split;
	char	*cmd_cpy;

	path = get_env("PATH");
	path_split = ft_split(path, ':');
	while (command)
	{
		cmd_cpy = command->cmd;
		if (!is_built_in(command->cmd))
			get_valid_cmd_handler(command, cmd_cpy, path_split);
		if (command->cmd)
		{
			exec_cmd(command, is_built_in(command->cmd));
			free_cmd(command);
		}
		command = command->next;
		if (command && !command->cmd)
			break ;
	}
	free_env_path(path_split);
	free(path);
	path = NULL;
	return (SUCCESS);
}
