/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:37:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/04 21:23:40 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	num;
	int					i;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || \
	str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		num = 10 * num + str[i++] - '0';
	return (sign * (int)num);
}

static void	putnbr(int n)
{
	char	num;

	if ((n / 10) == 0)
	{
		num = (n % 10) + '0';
		write(1, &num, 1);
		return ;
	}
	putnbr(n / 10);
	num = (n % 10) + '0';
	write(1, &num, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2147483648", 10);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		putnbr(-n);
	}
	else
		putnbr(n);
}

void	ft_putstr(char *s)
{
	int	len;

	if (!s)
		return ;
	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

void	ft_putendl(char *s)
{
	int	len;

	if (!s)
		return ;
	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
	write(1, "\n", 1);
}
