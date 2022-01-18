/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:05:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/18 20:19:58 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int     deq_is_empty(t_deque *deq)
{
    if(deq->head == NULL)
        return (1);
    else
        return (0);
}

int    push_front(t_deque *deq, int data)
{
    t_dlist  *new;

    new = (t_dlist*)malloc(sizeof(t_dlist));
    if (!new)
        return (0);
    new->value = data;
    new->next = deq->head;
    if(deq_is_empty(deq))
        deq->tail = new;
    else
        deq->head->prev = new;
    deq->size++;
    new->prev = NULL;
    deq->head = new;
    return (1);
}

int    push_back(t_deque *deq, int data)
{
    t_dlist  *new;

    new = (t_dlist*)malloc(sizeof(t_dlist));
    if (!new)
        return (0);
    new->value = data;
    new->prev = deq->tail;
    if(deq_is_empty(deq))
        deq->head = new;
    else
        deq->tail->next = new;
    deq->size++;
    new->next = NULL;
    deq->tail = new;
    return (1);
}

int     pop_front(t_deque *deq)
{
    t_dlist *pop_node;
    int     pop_data;

    pop_node = deq->head;
    pop_data = pop_node->value;
    deq->head = pop_node->next;
    free(pop_node);

    if(deq->head == NULL)
        deq->tail = NULL;
    else
        deq->head->prev = NULL;
    deq->size--;
    return (pop_data);
}

int     pop_back(t_deque *deq)
{
    t_dlist *pop_node;
    int     pop_data;

    pop_node = deq->tail;
    pop_data = pop_node->value;
    deq->tail = pop_node->prev;
    free(pop_node);

    if(deq->tail == NULL)
        deq->head = NULL;
    else
        deq->tail->next = NULL;
    deq->size--;
    return (pop_data);
}