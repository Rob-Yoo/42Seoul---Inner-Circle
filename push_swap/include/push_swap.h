/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:43:58 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/19 19:40:20 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include "util.h"
# define ERROR 0
# define SUCCESS 1

typedef struct          s_list
{
    char                *op;
    struct  s_list      *next;
    struct  s_list      *prev;
}   t_list;

typedef struct          s_op
{
    t_list              *head;
    t_list              *tail;
}   t_op;

typedef struct          s_dlist
{
    int                 value;
    struct  s_dlist     *prev;
    struct  s_dlist     *next;
}   t_dlist;

typedef struct          s_deque
{
    int                 size;
    t_dlist             *head;
    t_dlist             *tail;
}   t_deque;

typedef struct          s_all
{
    t_deque             *deq_A;
    t_deque             *deq_B;
    t_op                *op_list;
}   t_all;

// error.c
int                     find_duplicate(int v, t_dlist *head);
void                    free_all(t_all *all);
void                    throw_error(t_all *all);

// deque.c
int                     deq_is_empty(t_deque *deq);
int                     push_front(t_deque *deq, int data);
int                     push_back(t_deque *deq, int data);
int                     pop_front(t_deque *deq);
int                     pop_back(t_deque *deq);

// operation.c
void                    swap(char name, t_all *all);
void                    push(char to, t_all *all);
void                    rotate(char name, t_all *all);
void                    r_rotate(char name, t_all *all);
void                    print_op(t_op *op_list);

// operation_list.c
int                     add_op_list(t_op *op_list, char *op);

// push_swap.c
void                    init_push_swap(t_all *all);


#endif
