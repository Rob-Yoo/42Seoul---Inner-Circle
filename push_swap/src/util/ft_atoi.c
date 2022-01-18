/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 21:49:08 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/15 16:57:00 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	num;
	int					i;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			num = 10 * num + str[i++] - '0';
		else
			return (-1);
	}
	if ((sign == -1 && num > 2147483648) || num > 2147483647)
		return (-1);
	return (sign * (int)num);
}
