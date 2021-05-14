/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 20:08:39 by jinyoo            #+#    #+#             */
/*   Updated: 2021/05/14 14:16:13 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_strcnt(char const *str, char c)
{
	int		str_cnt;

	str_cnt = 0;
	while (*str)
	{
		if (*str != c)
		{
			str_cnt++;
			while (*str && (*str != c))
				str++;
		}
		str++;
	}
	return (str_cnt);
}

static void			ft_strcpy(char *dest, char const *start, char const *end)
{
	while (start < end)
		*(dest++) = *(start++);
	*dest = 0;
}

static int			split_handler(char **ret, char const *str, char c)
{
	int			idx;
	char const	*start;

	idx = 0;
	while (*str)
	{
		if (*str != c)
		{
			start = str;
			while (*str && (*str != c))
				str++;
			ret[idx] = (char*)malloc(str - start + 1);
			if (!ret[idx])
			{
				while (--idx >= 0)
					free(ret[idx]);
				return (1);
			}
			ft_strcpy(ret[idx++], start, str);
		}
		str++;
	}
	ret[idx] = 0;
	return (0);
}

char				**ft_split(char const *str, char c)
{
	char	**ret;
	int		str_cnt;

	if (!str)
		return (NULL);
	str_cnt = ft_strcnt(str, c);
	ret = (char**)malloc(sizeof(char *) * (str_cnt + 1));
	if (!ret)
		return (NULL);
	if (split_handler(ret, str, c))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
