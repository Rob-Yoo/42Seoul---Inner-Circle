/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 03:30:11 by jinyoo            #+#    #+#             */
/*   Updated: 2022/02/01 17:18:47 by jinyoo           ###   ########.fr       */
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
	free(del_node);
}

static int	minimize_op_list(t_op *op_list, char *op, char *prev_op)
{
	int		flag;
	char	*new_op;

	flag = 1;
	new_op = NULL;
	if ((!ft_strncmp(prev_op, "ra", 3) && !ft_strncmp(op, "rb", 3)) || \
		(!ft_strncmp(prev_op, "rb", 3) && !ft_strncmp(op, "ra", 3)))
		new_op = "rr";
	else if ((!ft_strncmp(prev_op, "rra", 3) && !ft_strncmp(op, "rrb", 3)) || \
			(!ft_strncmp(prev_op, "rrb", 3) && !ft_strncmp(op, "rra", 3)))
		new_op = "rrr";
	else if ((!ft_strncmp(prev_op, "sa", 3) && !ft_strncmp(op, "sb", 3)) || \
			(!ft_strncmp(prev_op, "sb", 3) && !ft_strncmp(op, "sa", 3)))
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
	if ((!ft_strncmp(prev_op, "pa", 3) && !ft_strncmp(op, "pb", 3)) || \
		(!ft_strncmp(prev_op, "pb", 3) && !ft_strncmp(op, "pa", 3)) || \
		(!ft_strncmp(prev_op, "ra", 3) && !ft_strncmp(op, "rra", 3)) || \
		(!ft_strncmp(prev_op, "rb", 3) && !ft_strncmp(op, "rrb", 3)) || \
		(!ft_strncmp(prev_op, "rra", 3) && !ft_strncmp(op, "ra", 3)) || \
		(!ft_strncmp(prev_op, "rrb", 3) && !ft_strncmp(op, "rb", 3)) || \
		(!ft_strncmp(prev_op, "sa", 3) && !ft_strncmp(op, "sa", 3)) || \
		(!ft_strncmp(prev_op, "sb", 3) && !ft_strncmp(op, "sb", 3)) || \
		(!ft_strncmp(prev_op, "rr", 3) && !ft_strncmp(op, "rrr", 3)) || \
		(!ft_strncmp(prev_op, "rrr", 3) && !ft_strncmp(op, "rr", 3)))
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
