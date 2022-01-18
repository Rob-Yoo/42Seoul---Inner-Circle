/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operationList.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 03:30:11 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/18 20:38:51 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int  add_last(t_oprt *op_list, char *oprt)
{
    t_list  *new;

    new = (t_list*)malloc(sizeof(t_list));
    if (!new)
        return (-1);
    if (op_list->head == NULL)
    {
        op_list->head = new;
        op_list->tail = new;
        new->operate = oprt;
        new->next = NULL;
        new->prev = NULL;
    }
    else
    {
        op_list->tail->next = new;
        new->prev = op_list->tail;
        new->next = NULL;
        new->operate = oprt;
        op_list->tail = new;
    }
    return (1);
}

static void delete_last(t_oprt *op_list)
{
    t_list    *del_node;

    del_node = op_list->tail;
    del_node->prev->next = NULL;
    op_list->tail = del_node->prev;
    free(op_list->tail);
}

static int  minimize_oprt(t_oprt *op_list, char *oprt, char *prev_oprt)
{
    int ret;

    ret = 0;
    if ((prev_oprt == "ra" && oprt == "rb") || \
        (prev_oprt == "rb" && oprt == "ra"))
        {
            delete_last(op_list);
            if (add_last(op_list, "rr") == -1)
                return (-1);
            ret = 1;
        }
    else if ((prev_oprt == "rra" && oprt == "rrb") || \
            (prev_oprt == "rrb" && oprt == "rra"))
        {
            delete_last(op_list);
            if (add_last(op_list, "rrr") == -1)
                return (-1);
            ret = 1;
        }
    else if ((prev_oprt == "sa" && oprt == "sb") || \
            (prev_oprt == "sb" && oprt == "sa"))
        {
            delete_last(op_list);
            if (add_last(op_list, "ss") == -1)
                return (-1);
            ret = 1;
        }
    return (ret);
}

static int  optimize_oprt_list(t_oprt *op_list, char *oprt, char *prev_oprt)
{   
    int ret;

    ret = 0;
    if ((prev_oprt == "pa" && oprt == "pb") || \
        (prev_oprt == "pb" && oprt == "pa") || \
        (prev_oprt == "ra" && oprt == "rra") || \
        (prev_oprt == "rb" && oprt == "rrb") || \
        (prev_oprt == "rra" && oprt == "ra") || \
        (prev_oprt == "rrb" && oprt == "rb") || \
        (prev_oprt == "sa" && oprt == "sa") || \
        (prev_oprt == "sb" && oprt == "sb") || \
        (prev_oprt == "rr" && oprt == "rrr") || \
        (prev_oprt == "rrr" && oprt == "rr"))
        {
            delete_last(op_list);
            ret = 1;
        }
    else
    {
        ret = minimize_oprt(op_list, oprt, prev_oprt);
        if (ret == -1)
            return (-1);
    }
    return (ret);
}

int set_oprt_list(t_oprt *op_list, char *oprt)
{
    char    *prev_oprt;
    int     ret;

    if (op_list->head == NULL)
    {
        add_last(op_list, oprt);
        return;
    }
    else
        prev_oprt = op_list->tail->operate;
    ret = optimize_oprt_list(op_list, oprt, prev_oprt);
    if (ret == 0)
        add_last(op_list, oprt);
    else if (ret == -1)
        return (0);
    return (1);
}