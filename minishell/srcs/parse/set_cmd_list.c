/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:00:32 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/10 21:01:52 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redir(t_cmd *cur, char **commands, int *i)
{
	if (commands[*i][0] == HEREDOC)
		return (handle_heredoc(cur, ft_strdup(commands[*i + 1]), i));
	else if (commands[*i][0] == REDIR_L)
		return (handle_redir(cur, REDIR_L, ft_strdup(commands[*i + 1]), i));
	else if (commands[*i][0] == REDIR_RR)
		return (handle_redir(cur, REDIR_RR, ft_strdup(commands[*i + 1]), i));
	else if (commands[*i][0] == REDIR_R)
		return (handle_redir(cur, REDIR_R, ft_strdup(commands[*i + 1]), i));
	return (0);
}

static void	set_not_output_file(int *i_argv, t_cmd *cur)
{
	cur->argv[(*i_argv)++] = ft_strdup("touch");
	cur->argv[(*i_argv)++] = ft_strdup(cur->output->file_name);
	cur->cmd = cur->argv[0];
	return ;
}

void	set_cmd_list(char **commands, t_cmd	*cur, int i, int i_argv)
{
	while (commands[++i] && cur)
	{
		if (commands[i][0] == PIPE_TYPE)
		{
			cur->is_pipe = 1;
			cur->pipe[0] = 0;
			cur->pipe[1] = 0;
			cur = cur->next;
			i_argv = 0;
		}
		else if (check_redir(cur, commands, &i))
		{
			if (i == 0)
				return ;
			if ((commands[i - 1][0] == REDIR_R || \
			commands[i - 1][0] == REDIR_RR) &&
			cur->output->file_name && cur->cmd == NULL)
				set_not_output_file(&i_argv, cur);
		}
		else
		{
			cur->argv[i_argv++] = ft_strdup(commands[i]);
			cur->cmd = cur->argv[0];
		}
	}
}
