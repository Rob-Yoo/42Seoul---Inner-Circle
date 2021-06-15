/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:10:00 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/15 22:09:55 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_write(char c, t_inform *inform)
{
	write(1, &c, 1);
	inform->size += 1;
}

void			width_handler(va_list ap, char w, t_inform *inform)
{
	int		arg;

	if (w == '*')
	{
		arg = va_arg(ap, int);
		if (arg < 0 && inform->flag == '-')
			inform->width = -arg;
		else if (arg < 0)
		{
			inform->width = -arg;
			inform->flag = '-';
		}
		else
			inform->width = arg;
	}
	else
		inform->width = inform->width * 10 + w - '0';
	inform->width_flag = 1;
}

void			prec_handler(va_list ap, char p, t_inform *inform)
{
	int		arg;

	if (p == '*')
	{
		arg = va_arg(ap, int);
		if (arg >= 0)
			inform->prec = arg;
	}
	else
		inform->prec = inform->prec * 10 + p - '0';
}

int				specifier_handler(va_list ap, char spec, t_inform *inform)
{
	if (spec == 'c')
		ft_printf_c(ap, inform);
	if (spec == 'd' || spec == 'i')
		ft_printf_int(ap, inform);
	return (1);
}

void			init_inform(t_inform *inform, int sign)
{
	if (sign)
		inform->size = 0;
	inform->flag = 0;
	inform->width = 0;
	inform->prec = 0;
	inform->prec_flag = 0;
	inform->width_flag = 0;
}