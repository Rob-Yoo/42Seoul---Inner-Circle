/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:48:34 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 00:42:49 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
	{
		len = ft_strlen(s);
		temp = (char *)malloc(sizeof(char) * (len - start + 1));
	}
	else
		temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	while (i < len && s[start] && start < ft_strlen(s))
		temp[i++] = s[start++];
	temp[i] = '\0';
	return (temp);
}
