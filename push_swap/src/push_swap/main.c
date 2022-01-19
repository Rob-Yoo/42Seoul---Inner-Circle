/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:43:02 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/19 19:41:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void init(t_deque *deq_A, t_deque *deq_B, t_op *op_list, t_all *all)
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

static void *set_A(char *arg, t_all *all)
{
    int     data;

    data = ft_atoi(arg);
    if (!data)
        throw_error(all);
    if (!find_duplicate(data, all->deq_A->head))
        throw_error(all);
    push_back(all->deq_A, data);
}


int main(int argc, char *argv[])
{
    t_all   all;
    t_deque deq_A;
    t_deque deq_B;
    t_op    op_list;
    int     i;

    if (argc > 1) {
        i = 0;
        init(&deq_A, &deq_B, &op_list, &all);
        while (++i < argc)
            set_A(argv[i], &all);
        init_push_swap(&all);
        print_op(&op_list);
        free_all(&all);
    }
    return (0);
}