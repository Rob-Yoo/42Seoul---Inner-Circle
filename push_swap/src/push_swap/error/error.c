/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:33:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/18 19:58:27 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int     find_duplicate(int v, t_dlist *tail)
{
    while(tail)
    {
        if (tail->value == v)
            return (-1);
        else
            tail = tail->prev;
    }
    return (1);
}

void    free_all(t_all *all)
{
    t_list  *oprt_node;
    t_dlist *deq_node;

    deq_node = all->deq_A->head;
    while (deq_node)
    {
        all->deq_A->head = deq_node->next;
        free(deq_node);
        deq_node = all->deq_A->head;
    }
    deq_node = all->deq_B->head;
    while (deq_node)
    {
        all->deq_B->head = deq_node->next;
        free(deq_node);
        deq_node = all->deq_B->head;
    }
    oprt_node = all->op_list->head;
    while (oprt_node)
    {
        all->op_list->head = oprt_node->next;
        free(oprt_node);
        oprt_node = all->op_list->head;
    }
}

void    error_handler(int error, t_all *all)
{
    if (error == 1)
    {
        ft_putstr_fd("Missing Arguments!!!!\n", 1);
        exit(1);
    }
    else
    {
        free_all(all);
        ft_putstr_fd("Error\n", 1);
        exit(1);
    }
}