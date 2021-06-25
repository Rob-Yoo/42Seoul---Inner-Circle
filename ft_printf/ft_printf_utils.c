/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:10:00 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/25 15:06:07 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_write(char c, t_inform *inf)
{
	write(1, &c, 1);
	inf->size += 1;
}

void			width_handler(va_list ap, char w, t_inform *inf)
{
	int		arg;

	if (w == '*')
	{
		arg = va_arg(ap, int);
		if (arg < 0 && inf->flag == '-')
			inf->width = -arg;
		else if (arg < 0)
		{
			inf->width = -arg;
			inf->flag = '-';
		}
		else
			inf->width = arg;
	}
	else
		inf->width = inf->width * 10 + w - '0';
	inf->width_flag = 1;
}

void			prec_handler(va_list ap, char p, t_inform *inf)
{
	int		arg;

	if (p == '*')
	{
		arg = va_arg(ap, int);
		if (arg >= 0)
			inf->prec = arg;
		else
			inf->prec_flag = -1;
	}
	else
		inf->prec = inf->prec * 10 + p - '0';
}

int				specifier_handler(va_list ap, char spec, t_inform *inf)
{
	if (spec == 'c')
		ft_printf_c(ap, inf);
	else if (spec == 'd' || spec == 'i')
		ft_printf_int(ap, inf);
	else if (spec == 's')
		ft_printf_s(ap, inf);
	else if (spec == 'u')
		ft_printf_u(ap, inf);
	else if (spec == 'x' || spec == 'X')
	{
		if (!ft_printf_hex(ap, inf, spec))
			return (0);
	}
	else if (spec == 'p')
	{
		if (!ft_printf_p(ap, inf))
			return (0);
	}
	else
		return (0);
	return (1);
}

void			init_inform(t_inform *inf, int sign)
{
	if (sign)
		inf->size = 0;
	inf->zero = 0;
	inf->minus = 0;
	inf->flag = 0;
	inf->width = 0;
	inf->prec = 0;
	inf->prec_flag = 0;
	inf->width_flag = 0;
}
