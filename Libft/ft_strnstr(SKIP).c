/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:38:13 by jinyoo            #+#    #+#             */
/*   Updated: 2021/05/03 21:48:04 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char*	ft_strnstr(const char *big, const char *little, unsigned int len)
{
	char* tmp;
	unsigned int i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	if (!(*little))
		return ((char*) big);
	while (*big && i + 1 < len)
	{
		j = 0;
		if (*big == little[j])
		{
			tmp = (char *) big;
			while (little[j])
			{
				if (*big == little[j++])
					flag = 1;
				else
				{
					flag = 0;
					big--;
					break;
				}
				big++;
			}
		}
		if (flag)
			return (tmp);
		big++;	
		i++;
	}
	return (0);
}

int main(void)
{
	printf("%s", ft_strnstr("bcdbcd", "bcd", 4));
	return (0);
}