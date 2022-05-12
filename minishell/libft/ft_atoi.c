/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 14:30:56 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/10 14:34:15 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_digit(int num)
{
	if (num >= '0' && num <= '9')
		return (1);
	else
		return (0);
}

static int	is_space(char *c)
{
	if (*c == '\t' || *c == '\n' || *c == '\v' \
		|| *c == '\f' || *c == '\r' || *c == ' ')
		return (1);
	return (0);
}

static int	get_sign(char sign)
{
	if (sign == '+')
		return (1);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	char		*temp;

	temp = (char *)str;
	sign = 1;
	result = 0;
	i = 0;
	while (is_space(&temp[i]))
		i++;
	if (temp[i] == '-' || temp[i] == '+')
		sign *= get_sign(temp[i++]);
	while (is_digit(temp[i]))
	{
		result = (result * 10) + (temp[i] - '0');
		if (sign * result < -2147483648)
			return (0);
		else if (sign * result > 2147483647)
			return (-1);
		i++;
	}
	return ((int)(result * sign));
}
