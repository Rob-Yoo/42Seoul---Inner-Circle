/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:38:13 by jinyoo            #+#    #+#             */
/*   Updated: 2021/05/14 15:23:13 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	char	*start;
	int		cnt;

	if (!*little)
		return ((char *)big);
	while (*big && len)
	{
		if (*big == *little)
		{
			start = (char *)big;
			i = 0;
			cnt = 0;
			while (*big && little[i] && *(big++) == little[i++] && len--)
				cnt++;
			if ((int)ft_strlen(little) == cnt)
				return (start);
		}
		else
		{
			len--;
			big++;
		}
	}
	return (NULL);
}
