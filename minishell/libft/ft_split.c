/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 00:25:16 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/22 21:59:34 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**split_free(char **temp, size_t count)
{
	while (--count)
	{
		free(temp[count]);
		temp[count] = 0;
	}
	free(temp);
	temp = 0;
	return (NULL);
}

static char	**split_malloc(char **temp, char const *src, char c, size_t wc)
{
	size_t	i;
	size_t	start;
	size_t	count;

	i = 0;
	count = 0;
	start = 0;
	while (src[i] && count < wc)
	{
		if (src[i] != c)
		{
			start = i;
			while (src[i] && src[i] != c)
				i++;
			temp[count] = ft_substr(src, start, i - start);
			if (!temp[count])
				return (split_free(temp, count));
			count++;
		}
		else
			i++;
	}
	temp[count] = 0;
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	wc;
	char	**temp;

	i = 0;
	wc = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			wc++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	temp = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!temp)
		return (NULL);
	return (split_malloc(temp, s, c, wc));
}
