/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 15:10:35 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/18 15:39:37 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*t1;

	t1 = malloc(sizeof(t_list));
	if (!t1)
		return (0);
	t1->content = content;
	t1->next = 0;
	return (t1);
}
