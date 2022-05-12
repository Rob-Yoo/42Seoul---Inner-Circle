/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:56:02 by minjupar          #+#    #+#             */
/*   Updated: 2021/05/08 19:12:31 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*temp;
	unsigned char	*s;

	if (dest == src)
		return (dest);
	temp = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (len--)
		*temp++ = *s++;
	return (dest);
}
