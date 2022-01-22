/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:50:41 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/22 16:59:04 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1_p;
	const unsigned char	*s2_p;
	size_t				i;

	if (n == 0)
		return (0);
	i = 0;
	s1_p = (const unsigned char *)s1;
	s2_p = (const unsigned char *)s2;
	while (s1_p[i] && s2_p[i] && i < n)
	{
		if (s1_p[i] != s2_p[i])
			return (s1_p[i] - s2_p[i]);
		i++;
	}
	if (i == n)
		i--;
	return (s1_p[i] - s2_p[i]);
}
