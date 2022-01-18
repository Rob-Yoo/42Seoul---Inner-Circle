/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:49:33 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/18 20:39:15 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    swap(char name, t_all *all)
{
    int     val_1;
    int     val_2;
    char    *oprt;
    t_deque *deq;

    if (name == 'a')
    {
        deq = all->deq_A;
        oprt = "sa";
    }
    else
    {
        deq = all->deq_B;
        oprt = "sb";
    }
    if (deq->size < 2)
        return;
    val_1 = pop_front(deq);
    val_2 = pop_front(deq);
    if (!push_front(deq, val_1))
        error_handler(2, all);
    if (!push_front(&deq, val_2))
        error_handler(2, all);
    if (!set_oprt_list(all->op_list, oprt))
        error_handler(2, all);
}

void    push(char to, t_all *all)
{
    int     val;
    char    *oprt;
    t_deque *deq_from;
    t_deque *deq_to;

    if (to == 'a')
    {
        deq_from = all->deq_B;
        deq_to = all->deq_A;
        oprt = "pa";
    } 
    else 
    {
        deq_from = all->deq_A;
        deq_to = all->deq_B;
        oprt =  "pb";
    }
    if(deq_is_empty(deq_from))
        return;
    val = pop_front(deq_from);
    if (!push_front(deq_to, val))
        error_handler(2, all);
    if (!set_oprt_list(all->op_list, oprt))
        error_handler(2, all);
}

void    rotate(char name, t_all *all)
{
    int     val;
    char    *oprt;
    t_deque *deq;

    if (name == 'a')
    {
        deq = all->deq_A;
        oprt = "ra";
    }
    else
    {
        deq = all->deq_B;
        oprt = "rb";
    }
    if(deq_is_empty(deq))
        return;
    val = pop_front(deq);
    if(!push_back(deq, val))
        error_handler(2, all);
    if (!set_oprt_list(all->op_list, oprt))
        error_handler(2, all);
    return (1);
}

void    r_rotate(char name, t_all *all)
{
    int     val;
    char    *oprt;
    t_deque *deq;

    if (name == 'a')
    {
        deq = all->deq_A;
        oprt = "rra";
    }
    else
    {
        deq = all->deq_B;
        oprt = "rrb";
    }
    if(deq_is_empty(deq))
        return;
    val = pop_back(deq);
    if (!push_front(deq, val))
        error_handler(2, all);
    if (!set_oprt_list(all->op_list, oprt))
        error_handler(2, all);
    return (1);
}

void    print_oprt_list(t_oprt *op_list)
{
    t_list  *cur;

    cur = op_list->head;
    while (cur)
    {
        ft_putstr_fd(cur->operate, 1);
        cur = cur->next;
    }
}