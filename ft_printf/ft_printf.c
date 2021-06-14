/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:33:21 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/14 22:53:33 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		format_handler(va_list ap, const char **format, t_inform *inform)
{
	while (!ft_isalpha(**format))
	{
		if (**format == '-' || **format == '0')
			inform->flag = (f == '-') ? '-' : '0';
		else if (ft_isdigit(**format) || **format == '*')
		{
			if (inform->prec_flag)
				prec_handler(ap, **format, inform);
			else
				width_handler(ap, **format, inform);
		}
		else if (**format == '.')
			inform->prec_flag = 1;
		else if (**format == '%')
		{
			ft_putchar_fd(**format, 1);
			inform->size += 1;
			(*format)++;
			return (1);
		}
		else
			return (0);
		(*format)++;
	}
	return (1);
}

int		check_format(va_list ap, const char *format, t_inform *inform)
{
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, 1);
			inform->size += 1;
		}
		else
		{
			if (!format_handler(ap, &(++format), inform))
				return (0);
			specifier_handler(ap, *format, inform);
			inform->prec_flag = 0;
		}
		format++;
	}
	return (1);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_inform	inform;

	inform.size = 0;
	inform.flag = 0;
	inform.width = 0;
	inform.prec = 0;
	inform.prec_flag = 0;
	va_start(ap, format);
	if (!check_format(ap, format, &inform))
		return (ERROR);
	return (inform.size);
}

int main()
{
	printf("%d\n", ft_printf("%c\n", 'a'));
	printf("%d\n", ft_printf("%c\n", 'b'));
}