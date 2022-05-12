/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:10:50 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/18 15:42:58 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			s1_len;
	size_t			s2_len;
	char			*temp;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!temp)
		return (0);
	ft_strlcpy(temp, s1, s1_len + 1);
	ft_strlcpy(&temp[s1_len], s2, s2_len + 1);
	return (temp);
}
