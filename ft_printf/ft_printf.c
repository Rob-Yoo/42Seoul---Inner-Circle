/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:33:21 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/16 16:47:40 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		format_handler(va_list ap, const char **format, t_inform *inform)
{
	while (!ft_isalpha(**format))
	{
		if ((**format == '-' || **format == '0') && !inform->width_flag)
			inform->flag = (**format == '-') ? '-' : '0';
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
			ft_write(**format, inform);
			return (1);
		}
		(*format)++;
	}
	return (0);
}

int		check_format(va_list ap, const char *format, t_inform *inform)
{
	while (*format)
	{
		if (*format != '%')
			ft_write(*format, inform);
		else
		{
			format++;
			if (!format_handler(ap, &format, inform))
				if (!specifier_handler(ap, *format, inform))
					return (0);
			init_inform(inform, 0);
		}
		format++;
	}
	return (1);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_inform	inform;

	init_inform(&inform, 1);
	va_start(ap, format);
	if (!check_format(ap, format, &inform))
		return (ERROR);
	va_end(ap);
	return (inform.size);
}

int		main(void)
{
	int a;

	printf("%d\n", ft_printf("[%-*.*d]\n", 10, 4, -10));
	a = printf("[%-*.*d]\n", 10, 4, -10);
	printf("%d", a);
	
	// 값이 음수이고 정밀도가 존재할 때 0이 붙어야하는데 붙질 않음...
}
