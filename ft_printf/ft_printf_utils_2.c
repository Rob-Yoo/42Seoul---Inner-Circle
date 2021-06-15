/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:50:12 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/15 22:14:26 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_cnt(int n, int cnt)
{
	if ((n / 10) == 0)
		return (++cnt);
	return (ft_cnt(n / 10, ++cnt));
}

int				ft_cnt_nbr(int n)
{
	int		cnt;

	cnt = 0;
	if (n == -2147483648)
		return (11);
	else if (n < 0)
		cnt = ft_cnt(-n, 0) + 1;
	else
		cnt = ft_cnt(n, 0);
	return (cnt);
}

static void		putnbr_handler(int n)
{
	char num;

	if ((n / 10) == 0)
	{
		num = (n % 10) + '0';
		write(1, &num, 1);
		return ;
	}
	putnbr_handler(n / 10);
	num = (n % 10) + '0';
	write(1, &num, 1);
}

void			ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2147483648", 10);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		putnbr_handler(-n);
	}
	else
		putnbr_handler(n);
}