/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/11 16:27:05 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_path(char **path)
{
	int	i;

	i = 0;
	if (path)
	{
		while (path[i])
		{
			free(path[i]);
			path[i] = NULL;
			i++;
		}
		free(path);
		path = NULL;
	}
}

int	ft_twoptr_len(char **twoptr)
{
	int	i;

	i = 0;
	while (twoptr[i])
		i++;
	return (i);
}

void	ft_strjoin_char(char **dst, char ch)
{
	char	str[2];
	char	*temp;

	temp = *dst;
	str[0] = ch;
	str[1] = '\0';
	*dst = ft_strjoin(*dst, str);
	free(temp);
	temp = NULL;
}

int	count_pipe(char **commands)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (commands[i])
	{
		if (commands[i][0] == PIPE_TYPE)
			count++;
		i++;
	}
	return (count);
}

void	make_file(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT, 0644);
	close(fd);
}
