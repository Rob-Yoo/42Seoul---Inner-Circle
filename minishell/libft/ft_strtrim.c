/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 23:05:09 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/10 14:33:46 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			i;
	size_t			j;
	char			*temp;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	if (!*s1)
		return (ft_strdup((char *)s1));
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[j - 1] && ft_strrchr(set, s1[j - 1]) && i < j - 1)
		j--;
	temp = malloc(sizeof(char) * (j - i + 1));
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, &s1[i], j - i + 1);
	return (temp);
}
