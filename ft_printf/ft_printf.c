/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:33:21 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/26 15:35:23 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		flag_handler(t_inform *inf, char c)
{
	if (c == '-')
		inf->minus = 1;
	else
		inf->zero = 1;
	if (inf->minus && inf->zero)
		inf->flag = '-';
	else if (inf->minus)
		inf->flag = '-';
	else
		inf->flag = '0';
}

static int		format_handler(va_list ap, const char **format, t_inform *inf)
{
	while (!ft_isalpha(**format))
	{
		if ((**format == '-' || **format == '0') && !inf->width_flag\
		&& !inf->prec_flag)
			flag_handler(inf, **format);
		else if ((**format >= '0' && **format <= '9') || **format == '*')
		{
			if (inf->prec_flag)
				prec_handler(ap, **format, inf);
			else
				width_handler(ap, **format, inf);
		}
		else if (**format == '.')
			inf->prec_flag = 1;
		else if (**format == '%')
		{
			ft_printf_per(inf);
			return (0);
		}
		(*format)++;
	}
	return (1);
}

static int		check_format(va_list ap, const char *format, t_inform *inf)
{
	while (*format)
	{
		if (*format != '%')
			ft_write(*format, inf);
		else
		{
			format++;
			if (format_handler(ap, &format, inf))
				if (!specifier_handler(ap, *format, inf))
					return (0);
			init_inform(inf, 0);
		}
		format++;
	}
	return (1);
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	t_inform	inf;

	init_inform(&inf, 1);
	va_start(ap, format);
	if (!check_format(ap, format, &inf))
		return (ERROR);
	va_end(ap);
	return (inf.size);
}
