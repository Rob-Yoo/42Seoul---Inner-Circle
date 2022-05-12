/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 22:36:14 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/18 15:38:19 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(int n)
{
	size_t	len;

	len = 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long long	num;
	char		*temp;
	size_t		len;

	num = n;
	len = 0;
	if (num <= 0)
	{
		len = get_len(num) + 1;
		num = num * -1;
	}
	else
		len = get_len(num);
	temp = malloc(sizeof(char) * len + 1);
	if (!temp)
		return (0);
	temp[len] = '\0';
	while (len > 0)
	{
		temp[--len] = (num % 10) + '0';
		num = num / 10;
	}
	if (n < 0)
		temp[0] = '-';
	return (temp);
}
