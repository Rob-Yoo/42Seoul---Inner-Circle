/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 15:20:35 by jinyoo            #+#    #+#             */
/*   Updated: 2021/05/14 17:23:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_strcpy(char *dest, char *start, char *end)
{
	while (start <= end)
		*(dest++) = *(start++);
	*dest = '\0';
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*pos;
	char	*ret;

	if (!s1 || !set)
		return (NULL);
	while (*s1)
		if (!(ft_strchr(set, *(s1++))))
			break ;
	if (!*s1)
	{
		if (!(ret = (char *)malloc(1)))
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	pos = (char *)s1 + ft_strlen(s1) - 1;
	while (pos >= s1)
		if (!(ft_strchr(set, *(pos--))))
			break ;
	s1--;
	pos++;
	if (!(ret = (char *)malloc(sizeof(char) * (pos - s1 + 2))))
		return (NULL);
	ft_strcpy(ret, (char *)s1, pos);
	return (ret);
}
