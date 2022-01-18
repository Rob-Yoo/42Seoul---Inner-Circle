/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:43:58 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/18 20:17:19 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include "util.h"

typedef struct          s_list
{
    char                *operate;
    struct  s_list      *next;
    struct  s_list      *prev;
}   t_list;

typedef struct          s_oprt
{
    t_list              *head;
    t_list              *tail;
}   t_oprt;

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
    t_oprt              *op_list;
}   t_all;
// lst_util.c
// t_dlist                 *set_A_stack(char *arg, int idx, t_dlist *tail);
// void                    free_all(t_dlist *tail);

// error.c
int                     find_duplicate(int v, t_dlist *tail);
void                    error_handler(int error, t_all *all);
void                    free_all(t_all *all);

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
void                    print_oprt_list(t_oprt *op_list);

// operationList.c
int                     set_oprt_list(t_oprt *op_list, char *oprt);



#endif
