/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 03:30:11 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/20 16:50:54 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	add_last(t_op *op_list, char *op)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (ERROR);
	if (op_list->head == NULL)
	{
		op_list->head = new;
		op_list->tail = new;
		new->op = op;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		op_list->tail->next = new;
		new->prev = op_list->tail;
		new->next = NULL;
		new->op = op;
		op_list->tail = new;
	}
	return (SUCCESS);
}

static void	delete_last(t_op *op_list)
{
	t_list	*del_node;

	del_node = op_list->tail;
	del_node->prev->next = NULL;
	op_list->tail = del_node->prev;
	free(op_list->tail);
}

static int	minimize_op_list(t_op *op_list, char *op, char *prev_op)
{
	int		flag;
	char	*new_op;

	flag = 1;
	new_op = NULL;
	if ((prev_op == "ra" && op == "rb") || \
		(prev_op == "rb" && op == "ra"))
		new_op = "rr";
	else if ((prev_op == "rra" && op == "rrb") || \
			(prev_op == "rrb" && op == "rra"))
		new_op = "rrr";
	else if ((prev_op == "sa" && op == "sb") || \
			(prev_op == "sb" && op == "sa"))
		new_op = "ss";
	if (new_op)
	{
		delete_last(op_list);
		if (!add_last(op_list, new_op))
			return (ERROR);
		flag = 2;
	}
	return (flag);
}

static int	optimize_op_list(t_op *op_list, char *op, char *prev_op)
{
	int	flag;

	if ((prev_op == "pa" && op == "pb") || \
		(prev_op == "pb" && op == "pa") || \
		(prev_op == "ra" && op == "rra") || \
		(prev_op == "rb" && op == "rrb") || \
		(prev_op == "rra" && op == "ra") || \
		(prev_op == "rrb" && op == "rb") || \
		(prev_op == "sa" && op == "sa") || \
		(prev_op == "sb" && op == "sb") || \
		(prev_op == "rr" && op == "rrr") || \
		(prev_op == "rrr" && op == "rr"))
	{
		delete_last(op_list);
		return (SUCCESS);
	}
	flag = minimize_op_list(op_list, op, prev_op);
	if (!flag)
		return (ERROR);
	else if (flag == 1)
		add_last(op_list, op);
	return (SUCCESS);
}

int	add_op_list(t_op *op_list, char *op)
{
	char	*prev_op;

	if (op_list->head == NULL)
	{
		if (!add_last(op_list, op))
			return (ERROR);
		return (SUCCESS);
	}
	else
		prev_op = op_list->tail->op;
	if (!optimize_op_list(op_list, op, prev_op))
		return (ERROR);
	return (SUCCESS);
}
