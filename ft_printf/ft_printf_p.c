/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 20:06:54 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/23 21:33:43 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		left_sort(char *arg, int s_cnt, t_inform *inf)
{
	int		len;

	len = ft_strlen(arg);
	write(1, "0x", 2);
	write(1, arg, len);
	inf->size += len + 2;
	while (s_cnt--)
		ft_write(' ', inf);
}

static void		rgt_sort(char *arg, int s_cnt, t_inform *inf)
{
	int		len;

	len = ft_strlen(arg);
	while (s_cnt--)
		ft_write(' ', inf);
	write(1, "0x", 2);
	write(1, arg, len);
	inf->size += len + 2;
}

static void		width_controller(char *address, int len, t_inform *inf)
{
	if (inf->width > len)
	{
		if (inf->flag == '-')
			left_sort(address, inf->width - len, inf);
		else
			rgt_sort(address, inf->width - len, inf);
	}
	else
		rgt_sort(address, 0, inf);
}

static void		dot_controller(t_inform *inf)
{
	if (inf->flag == '-')
	{
		write(1, "0x", 2);
		inf->size += 2;
		if (inf->width > 2)
		{
			inf->width -= 2;
			while (inf->width--)
				ft_write(' ', inf);
		}
	}
	else
	{
		if (inf->width > 2)
		{
			inf->width -= 2;
			while (inf->width--)
				ft_write(' ', inf);
		}
		write(1, "0x", 2);
		inf->size += 2;
	}
}

int				ft_printf_p(va_list ap, t_inform *inf)
{
	void			*arg;
	char			*address;
	int				len;

	arg = va_arg(ap, void *);
	if (!(address = ft_hextoa((unsigned long long)arg)))
		return (0);
	len = (int)ft_strlen(address) + 2;
	if (inf->prec_flag && !arg)
		dot_controller(inf);
	else if (inf->width)
		width_controller(address, len, inf);
	else
		rgt_sort(address, 0, inf);
	free(address);
	return (1);
}
