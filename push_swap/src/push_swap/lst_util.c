/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:12:22 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/17 03:05:30 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    free_all(t_dlist *tail)
{
    t_dlist  *tmp;

    while(tail)
    {
        tmp = tail->prev;
        free(tail);
        tail = tmp;
    }
}

t_dlist    *set_A_stack(char *arg, int idx, t_dlist *tail)
{
    int     data;
    t_dlist  *new;

    data = ft_atoi(arg);
    if (data == -1)
        error_handler(2, tail);
    if(find_duplicate(data, tail) == -1)
        error_handler(2, tail);
    new = (t_dlist *)malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
    if (idx == 1)
    {
	    new->value = data;
	    new->next = NULL;
        new->prev = NULL;
    }
    else
    {
        new->value = data;
        new->next = NULL;
        tail->next = new; 
        new->prev = tail;
    }
    return (new);
}
