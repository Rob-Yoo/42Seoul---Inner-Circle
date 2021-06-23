/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 21:50:12 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/23 21:33:54 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_cnt(long long n, int cnt)
{
	if ((n / 10) == 0)
		return (++cnt);
	return (ft_cnt(n / 10, ++cnt));
}

int				ft_cnt_nbr(long long n)
{
	int		cnt;

	cnt = 0;
	if (n < 0)
		cnt = ft_cnt(-n, 0);
	else
		cnt = ft_cnt(n, 0);
	return (cnt);
}

static void		putnbr_handler(long long n)
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

void			ft_putnbr(long long n)
{
	if (n < 0)
		putnbr_handler(-n);
	else
		putnbr_handler(n);
}

char			*ft_toupper(char *s)
{
	char	*tmp;

	tmp = s;
	while (*tmp)
	{
		if (*tmp >= 'a' && *tmp <= 'z')
			*tmp -= 32;
		tmp++;
	}
	return (s);
}
