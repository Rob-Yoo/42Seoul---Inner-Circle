/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:00:57 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/18 15:43:09 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	destlen;
	unsigned int	srclen;
	unsigned int	result;
	unsigned int	i;

	destlen = ft_strlen(dest);
	srclen = ft_strlen((char *)src);
	result = 0;
	i = 0;
	if (size < destlen)
		return (srclen + size);
	else
	{
		while (src[i] && destlen + i + 1 < size)
		{
			dest[destlen + i] = src[i];
			i++;
		}
		dest[destlen + i] = '\0';
		return (destlen + srclen);
	}
}
