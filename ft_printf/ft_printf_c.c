/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:06:26 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/14 16:22:35 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_c(va_list ap, t_inform *inform)
{
	char c;

	c = va_arg(ap, int);
	ft_putchar_fd(c, 1);
	inform->size += 1;	
}