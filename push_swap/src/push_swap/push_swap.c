/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:43:02 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/18 20:25:03 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void init(t_deque *deq_A, t_deque *deq_B, t_oprt *op_list, t_all *all)
{
    deq_A->head = NULL;
    deq_A->tail = NULL;
    deq_A->size = 0;
    deq_B->head = NULL;
    deq_B->tail = NULL;
    deq_B->size = 0;
    op_list->head = NULL;
    op_list->tail = NULL;
    all->deq_A = deq_A;
    all->deq_B = deq_B;
    all->op_list = op_list;
}

int main(int argc, char *argv[])
{
    t_deque deq_A;
    t_deque deq_B;
    t_oprt  op_list;
    t_all   all;

    if (argc > 1) {
        init(&deq_A, &deq_B, &op_list, &all);
    }
    // p = NULL;

    // while (++i < argc)
    //     p = set_A_stack(argv[i], i, p);
    free_all(&all);
    return (0);
}