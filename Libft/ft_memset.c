/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:33:33 by jinyoo            #+#    #+#             */
/*   Updated: 2021/05/09 15:22:08 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *b_p;

	b_p = (unsigned char *)b;
	while (len--)
	{
		*b_p = (unsigned char)c;
		b_p++;
	}
	return (b);
}
