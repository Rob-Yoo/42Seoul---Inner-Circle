/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:05:02 by jinyoo            #+#    #+#             */
/*   Updated: 2021/06/15 17:58:56 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

void	ft_printf_int(va_list ap, t_inform *inform)
{
	int		arg;
	int		len;

	arg = va_list(ap, int);
	len = ft_cnt_nbr(arg);
}