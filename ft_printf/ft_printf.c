/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:33:21 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/10 22:28:56 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"



int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_inform	*inform;

	va_start(ap, format);
	
	return (inform->size);
}