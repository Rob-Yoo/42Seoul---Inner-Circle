/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:10:00 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/15 17:54:01 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_write(char c, t_inform *inform)
{
	write(1, &c, 1);
	inform->size += 1;
}

void			width_handler(va_list ap, char w, t_inform *inform)
{
	if (w == '*')
		inform->width = va_arg(ap, int);
	else
		inform->width = inform->width * 10 + w - '0';
}

void			prec_handler(va_list ap, char p, t_inform *inform)
{
	int		arg;

	if (p == '*')
	{
		arg = va_arg(ap, int);
		if (arg >= 0)
			inform->prec = arg;
	}
	else
		inform->prec = inform->prec * 10 + p - '0';
}

int				specifier_handler(va_list ap, char spec, t_inform *inform)
{
	if (spec == 'c')
		ft_printf_c(ap, inform);
	if (spec == 'd' || spec == 'i')
		ft_printf_int(ap, inform);
	return (1);
}

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