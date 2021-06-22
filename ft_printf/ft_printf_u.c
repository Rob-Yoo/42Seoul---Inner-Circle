/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 16:50:56 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/22 17:12:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		left_sort(unsigned int arg, int s_cnt, int z_cnt, t_inform *inf)
{
	while (z_cnt--)
		ft_write('0', inf);
	ft_putnbr(arg);
	while (s_cnt--)
		ft_write(' ', inf);
}

static void		rgt_sort(unsigned int arg, int s_cnt, int z_cnt, t_inform *inf)
{
	while (s_cnt--)
	{
		if (inf->flag == '0' && inf->prec_flag <= 0)
			ft_write('0', inf);
		else
			ft_write(' ', inf);
	}
	while (z_cnt--)
		ft_write('0', inf);
	ft_putnbr(arg);
}

static void		width_controller(unsigned int arg, int len, t_inform *inf)
{
	if (inf->prec > len)
	{
		if (inf->width > inf->prec)
		{
			if (inf->flag == '-')
				left_sort(arg, inf->width - inf->prec, inf->prec - len, inf);
			else
				rgt_sort(arg, inf->width - inf->prec, inf->prec - len, inf);
		}
		else
			rgt_sort(arg, 0, inf->prec - len, inf);
	}
	else
	{
		if (inf->width > len)
		{
			if (inf->flag == '-')
				left_sort(arg, inf->width - len, 0, inf);
			else
				rgt_sort(arg, inf->width - len, 0, inf);
		}
		else
			rgt_sort(arg, 0, 0, inf);
	}
}

static void		precision_controller(unsigned int arg, int len, t_inform *inf)
{
	if (inf->prec > len)
		rgt_sort(arg, 0, inf->prec - len, inf);
	else
		rgt_sort(arg, 0, 0, inf);
}

void			ft_printf_u(va_list ap, t_inform *inf)
{
	unsigned int		arg;
	int					len;

	arg = va_arg(ap, unsigned int);
	len = ft_cnt_nbr(arg);
	if (arg == 0 && inf->prec_flag == 1 && inf->prec == 0)
	{
		while (inf->width--)
			ft_write(' ', inf);
		return ;
	}
	inf->size += len;
	if (inf->width)
		width_controller(arg, len, inf);
	else if (inf->prec)
		precision_controller(arg, len, inf);
	else
		rgt_sort(arg, 0, 0, inf);
}
