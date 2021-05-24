/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 23:22:14 by jinyoo            #+#    #+#             */
/*   Updated: 2021/05/24 13:27:59 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		get_newline_idx(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		get_one_line(char **backup, char **line, int newline_idx)
{
	char	*tmp;

	(*backup)[newline_idx] = '\0';
	*line = ft_strdup(*backup);
	if (ft_strlen(*backup + newline_idx + 1) == 0)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	tmp = ft_strdup(*backup + newline_idx + 1);
	free(*backup);
	*backup = tmp;
	return (1);
}

int		get_last_line(char **backup, char **line, int size)
{
	int		newline_idx;

	if (size < -1)
		return (-1);
	if (*backup && ((newline_idx = get_newline_idx(*backup)) >= 0))
		return (get_one_line(backup, line, newline_idx));
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				size;
	int				newline_idx;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[size] = '\0';
		backup[fd] = ft_strjoin(backup[fd], buf);
		if ((newline_idx = get_newline_idx(backup[fd])) >= 0)
			return (get_one_line(&backup[fd], line, newline_idx));
	}
	return (get_last_line(&backup[fd], line, size));
}
