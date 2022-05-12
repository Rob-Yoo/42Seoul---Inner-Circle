/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:43:30 by minjupar          #+#    #+#             */
/*   Updated: 2021/05/11 00:21:57 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	target;
	size_t			i;

	target = (unsigned char)c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == target)
			return ((char *)(s + i));
		i--;
	}
	if (s[i] == target)
		return ((char *)(s + i));
	return (NULL);
}
