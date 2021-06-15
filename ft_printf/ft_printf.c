/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:33:21 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/15 16:23:53 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		format_handler(va_list ap, const char **format, t_inform *inform)
{
	while (!ft_isalpha(**format))
	{
		if (**format == '-' || **format == '0')
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
	va_end(ap);
	return (inform.size);
}

int		main(void)
{
	int n = 10;
	char c = 'a';
	int i;
	int a[30];

	a[1]=printf("1 >%*c<\n", n, c);
	a[2]=printf("2 >%-*c<\n", n, c);
	a[3]=printf("3 >%*.c<\n", n, c);
	a[4]=printf("4 >%-c<\n", c);
	a[5]=printf("5 >%-.c<\n", c);
	a[6]=printf("6 >%.c<\n", c);
	a[7]=printf("9 >%.c<\n\n", c);

	a[11]=ft_printf("1 >%*c<\n", n, c);
	a[12]=ft_printf("2 >%-*c<\n", n, c);
	a[13]=ft_printf("3 >%*.c<\n", n, c);
	a[14]=ft_printf("4 >%-c<\n", c);
	a[15]=ft_printf("5 >%-.c<\n", c);
	a[16]=ft_printf("6 >%.c<\n", c);
	a[17]=ft_printf("9 >%.c<\n\n", c);
	for(i=1;i<7;i++)
		printf("%3d %3d %3d\n", a[i], a[i+10], a[i] == a[i+10]);
	return (0);
}
