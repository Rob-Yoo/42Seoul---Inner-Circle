/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/20 19:27:43 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_quote(char c, char *flag)
{
	if (c == '\'' || c == '"')
	{
		if (*flag == 0)
			*flag = c;
		else if (c == '\'' && *flag == '\'')
			*flag = 0;
		else if (c == '"' && *flag == '"')
			*flag = 0 ;
	}
	return ;
}

static int	get_word_count(char *str)
{
	int		i;
	char	flag;
	int		word_count;

	flag = 0;
	i = -1;
	word_count = 0;
	while (str[++i])
	{
		change_quote(str[i], &flag);
		if (flag == 0 && str[i + 1] == '\0')
			word_count++;
		else if (flag == 0 && str[i] != ' ' && str[i + 1] == ' ' )
		{
			word_count++;
			i++;
		}
	}
	return (word_count);
}

static int	get_word_len(int start, char*str)
{
	char	flag;
	int		len;

	flag = 0;
	len = 0;
	while (str[start + len])
	{
		change_quote(str[start + len], &flag);
		if (flag == 0 && str[start + len] == ' ')
			return (len);
		len++;
	}
	return (len);
}

static int	get_start(int start, char *str)
{
	while (str[start] && (str[start] == ' '))
		start ++;
	return (start);
}

char	**ft_split_cmds(char *str)
{
	int		i;
	int		word_len;
	int		start;
	int		word_cnt;
	char	**command_array;

	word_cnt = get_word_count(str);
	command_array = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!command_array)
		ft_error();
	i = -1;
	start = get_start(0, str);
	while (++i < word_cnt)
	{
		word_len = get_word_len(start, str);
		command_array[i] = (char *)malloc(sizeof(char) * (word_len +1));
		if (!command_array[i])
			ft_error();
		ft_strlcpy(command_array[i], str + start, word_len + 1);
		start = get_start(start + word_len, str);
	}
	command_array[i] = NULL;
	return (command_array);
}
