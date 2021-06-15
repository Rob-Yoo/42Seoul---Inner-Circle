/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:06:26 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/15 16:09:19 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_c(va_list ap, t_inform *inform)
{
	char c;

	c = va_arg(ap, int);
	if (inform->width && inform->flag == '-')
	{
		ft_write(c, inform);
		while (--inform->width)
			ft_write(' ', inform);
	}
	else if (inform->width)
	{
		while (--inform->width)
			ft_write(' ', inform);
		ft_write(c, inform);
	}
	else
		ft_write(c, inform);
}
