/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:06:26 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/22 19:16:20 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_c(va_list ap, t_inform *inf)
{
	char c;

	c = va_arg(ap, int);
	if (inf->width && inf->flag == '-')
	{
		ft_write(c, inf);
		while (--inf->width)
			ft_write(' ', inf);
	}
	else if (inf->width)
	{
		while (--inf->width)
			ft_write(' ', inf);
		ft_write(c, inf);
	}
	else
		ft_write(c, inf);
}

void	ft_printf_per(t_inform *inf)
{
	if (inf->width && inf->flag == '-')
	{
		ft_write('%', inf);
		while (--inf->width)
			ft_write(' ', inf);
	}
	else if (inf->width)
	{
		if (inf->flag == '0')
			while (--inf->width)
				ft_write('0', inf);
		else
			while (--inf->width)
				ft_write(' ', inf);
		ft_write('%', inf);
	}
	else
		ft_write('%', inf);
}
