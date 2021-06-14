/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:10:00 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/14 22:53:32 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	width_handler(va_list ap, char w, t_inform *inform)
{
	if (w == '*')
		inform->width = va_arg(ap, int);
	else
		inform->width = inform->width * 10 + w - '0';
}

void	prec_handler(va_list ap, char p, t_inform *inform)
{
	if (w == '*')
		inform->prec = va_arg(ap, int);
	else
		inform->prec = inform->prec * 10 + p - '0';
}

void	specifier_handler(va_list ap, char spec, t_inform *inform)
{
	if (spec == 'c')
		ft_printf_c(ap, inform);
}