/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:21:04 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/16 18:26:15 by jinyoo           ###   ########.fr       */
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

static void		right_sort(int arg, int sp_cnt, int zero_cnt, t_inform *inf)
{
	if (arg < 0 && sp_cnt > 0)
		sp_cnt--;
	while (sp_cnt--)
		ft_write(' ', inf);
	if (arg < 0)
		ft_write('-', inf);
	while (zero_cnt--)
		ft_write('0', inf);
	ft_putnbr(arg);
}

static void		width_prec_comb(int arg, int len, t_inform *inf)
{
	if (inf->flag == '-')
		left_sort(arg, inf->width - inf->prec, inf->prec - len, inf);
	else if (inf->flag == '0' || !inf->flag)
		right_sort(arg, inf->width - inf->prec, inf->prec - len, inf);
}

static void		width_len_comb(int arg, int len, t_inform *inf)
{
	if (inf->flag == '-')
		left_sort(arg, inf->width - len, 0, inf);
	else if (inf->flag == '0')
		right_sort(arg, 0, inf->width - len, inf);
	else if (!inf->flag)
		right_sort(arg, inf->width - len, 0, inf);
}

void			ft_printf_s(va_list ap, t_inform *inf)
{
	int		arg;
	int		len;

	arg = va_arg(ap, char *);
	len = ft_strlen(arg);
	inf->size += len;
	if (inf->width > inf->prec && inf->prec > len)
		width_prec_comb(arg, len, inf);
	else if (inf->width > inf->prec)
		width_len_comb(arg, len, inf);
	else if (inf->prec > len)
		right_sort(arg, 0, inf->prec - len, inf);
	else
		ft_putnbr(arg);
}