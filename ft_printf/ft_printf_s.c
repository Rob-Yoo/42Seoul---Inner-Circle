/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:21:04 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/22 16:48:32 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		left_sort(char *arg, int sp_cnt, t_inform *inf, int s)
{
	int		len;

	if (!arg)
	{
		if (inf->prec_flag <= 0)
			len = 6;
		else
			len = (inf->prec > 6) ? 6 : inf->prec;
		write(1, "(null)", len);
		inf->size += len;
	}
	else if (s == 1)
	{
		write(1, arg, (int)ft_strlen(arg));
		inf->size += (int)ft_strlen(arg);
	}
	else if (s == 2)
	{
		write(1, arg, inf->prec);
		inf->size += inf->prec;
	}
	while (sp_cnt--)
		ft_write(' ', inf);
}

static void		right_sort(char *arg, int sp_cnt, t_inform *inf, int s)
{
	int		len;

	while (sp_cnt--)
		ft_write(' ', inf);
	if (!arg && s != 0)
	{
		if (inf->prec_flag <= 0)
			len = 6;
		else
			len = (inf->prec > 6) ? 6 : inf->prec;
		write(1, "(null)", len);
		inf->size += len;
	}
	else if (s == 1)
	{
		write(1, arg, (int)ft_strlen(arg));
		inf->size += (int)ft_strlen(arg);
	}
	else if (s == 2)
	{
		write(1, arg, inf->prec);
		inf->size += inf->prec;
	}
}

static void		width_controller(char *arg, int len, t_inform *inf)
{
	if (inf->prec > len)
	{
		if (inf->width > len)
		{
			if (inf->flag == '-')
				left_sort(arg, inf->width - len, inf, 1);
			else
				right_sort(arg, inf->width - len, inf, 1);
		}
		else
			right_sort(arg, 0, inf, 1);
	}
	else
	{
		if (inf->width > inf->prec)
		{
			if (inf->flag == '-')
				left_sort(arg, inf->width - inf->prec, inf, 2);
			else
				right_sort(arg, inf->width - inf->prec, inf, 2);
		}
		else
			right_sort(arg, 0, inf, 2);
	}
}

static void		minus_zero_prec_controller(char *arg, int len, t_inform *inf)
{
	if (inf->width > len)
	{
		if (inf->flag == '-')
			left_sort(arg, inf->width - len, inf, 1);
		else
			right_sort(arg, inf->width - len, inf, 1);
	}
	else
		right_sort(arg, 0, inf, 1);
}

void			ft_printf_s(va_list ap, t_inform *inf)
{
	char	*arg;
	int		len;

	arg = va_arg(ap, char *);
	if (arg)
		len = (int)ft_strlen(arg);
	else
		len = 6;
	if (inf->prec_flag == 1 && inf->prec == 0)
		right_sort(arg, inf->width, inf, 0);
	else if (inf->prec_flag < 0 || inf->prec == 0)
		minus_zero_prec_controller(arg, len, inf);
	else if (inf->width)
		width_controller(arg, len, inf);
	else if (inf->prec)
	{
		if (inf->prec > len)
			right_sort(arg, 0, inf, 1);
		else
			right_sort(arg, 0, inf, 2);
	}
	else
		right_sort(arg, 0, inf, 1);
}
