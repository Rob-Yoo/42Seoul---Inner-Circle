/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:31:17 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/23 21:32:47 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		left_sort(char *arg, int s_cnt, int z_cnt, t_inform *inf)
{
	int		len;

	len = ft_strlen(arg);
	while (z_cnt--)
		ft_write('0', inf);
	write(1, arg, len);
	inf->size += len;
	while (s_cnt--)
		ft_write(' ', inf);
}

static void		rgt_sort(char *arg, int s_cnt, int z_cnt, t_inform *inf)
{
	int		len;

	len = ft_strlen(arg);
	while (s_cnt--)
	{
		if (inf->flag == '0' && inf->prec_flag <= 0)
			ft_write('0', inf);
		else
			ft_write(' ', inf);
	}
	while (z_cnt--)
		ft_write('0', inf);
	write(1, arg, len);
	inf->size += len;
}

static void		width_controller(char *arg, int len, t_inform *inf)
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

static void		precision_controller(char *arg, int len, t_inform *inf)
{
	if (inf->prec > len)
		rgt_sort(arg, 0, inf->prec - len, inf);
	else
		rgt_sort(arg, 0, 0, inf);
}

int				ft_printf_hex(va_list ap, t_inform *inf, char spec)
{
	unsigned int	arg;
	char			*hex_string;
	int				len;

	arg = va_arg(ap, unsigned int);
	if (arg == 0 && inf->prec_flag == 1 && inf->prec == 0)
	{
		while (inf->width--)
			ft_write(' ', inf);
		return (1);
	}
	if (!(hex_string = ft_hextoa(arg)))
		return (0);
	if (spec == 'X')
		hex_string = ft_toupper(hex_string);
	len = (int)ft_strlen(hex_string);
	if (inf->width)
		width_controller(hex_string, len, inf);
	else if (inf->prec)
		precision_controller(hex_string, len, inf);
	else
		rgt_sort(hex_string, 0, 0, inf);
	free(hex_string);
	return (1);
}
