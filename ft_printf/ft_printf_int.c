/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:05:02 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/20 20:56:49 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		left_sort(int arg, int sp_cnt, int zero_cnt, t_inform *inf)
{
	if (arg < 0)
	{
		ft_write('-', inf);
		if (sp_cnt > 0)
			sp_cnt--;
	}
	while (zero_cnt--)
		ft_write('0', inf);
	ft_putnbr(arg);
	while (sp_cnt--)
		ft_write(' ', inf);
}

static void		right_sort(int arg, int sp_cnt, int z_cnt, t_inform *inf)
{
	int		sign;

	sign = 1;
	if (arg < 0 && sp_cnt > 0)
	{
		if (inf->flag == '0' && inf->prec_flag <= 0)
		{
			ft_write('-', inf);
			sign = 0;
		}
		sp_cnt--;
	}
	while (sp_cnt--)
	{
		if (inf->flag == '0' && inf->prec_flag <= 0)
			ft_write('0', inf);
		else
			ft_write(' ', inf);
	}
	if (arg < 0 && sign)
		ft_write('-', inf);
	while (z_cnt--)
		ft_write('0', inf);
	ft_putnbr(arg);
}

static void		width_controller(int arg, int len, t_inform *inf)
{
	if (inf->prec > len)
	{
		if (inf->width > inf->prec)
		{
			if (inf->flag == '-')
				left_sort(arg, inf->width - inf->prec, inf->prec - len, inf);
			else
				right_sort(arg, inf->width - inf->prec, inf->prec - len, inf);
		}
		else
			right_sort(arg, 0, inf->prec - len, inf);
	}
	else
	{
		if (inf->width > len)
		{
			if (inf->flag == '-')
				left_sort(arg, inf->width - len, 0, inf);
			else
				right_sort(arg, inf->width - len, 0, inf);
		}
		else
			right_sort(arg, 0, 0, inf);
	}
}

static void		precision_controller(int arg, int len, t_inform *inf)
{
	if (inf->prec > len)
		right_sort(arg, 0, inf->prec - len, inf);
	else
		right_sort(arg, 0, 0, inf);
}

void			ft_printf_int(va_list ap, t_inform *inf)
{
	int		arg;
	int		len;

	arg = va_arg(ap, int);
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
		right_sort(arg, 0, 0, inf);
}
