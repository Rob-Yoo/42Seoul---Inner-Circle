/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 23:25:56 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/18 15:42:14 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	target;
	int				i;

	target = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == target)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == target)
		return ((char *)(s + i));
	return (NULL);
}
