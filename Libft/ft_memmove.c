/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 15:23:35 by jinyoo            #+#    #+#             */
/*   Updated: 2021/05/14 17:42:18 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char		*src_p;
	unsigned char	*dst_p;

	if (dst == src)
		return (dst);
	if (dst < src)
	{
		dst_p = dst;
		src_p = src;
		while (len--)
			*(dst_p++) = *(src_p++);
	}
	else
	{
		dst_p = dst;
		dst_p += len;
		src_p = src;
		src_p += len;
		while (len--)
			*(--dst_p) = *(--src_p);
	}
	return (dst);
}
