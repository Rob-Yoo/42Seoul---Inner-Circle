/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:28:38 by minjupar          #+#    #+#             */
/*   Updated: 2021/05/06 17:04:12 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int value, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)dest;
	while (len--)
		ptr[len] = (unsigned char)value;
	return (dest);
}
