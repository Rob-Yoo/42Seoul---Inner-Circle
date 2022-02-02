/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 22:49:33 by jinyoo            #+#    #+#             */
/*   Updated: 2022/02/01 17:19:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(char name, t_all *all)
{
	int		val_1;
	int		val_2;
	char	*op;
	t_deque	*deq;

	if (name == 'a')
	{
		deq = all->deq_A;
		op = "sa";
	}
	else
	{
		deq = all->deq_B;
		op = "sb";
	}
	if (deq->size < 2)
		return ;
	val_1 = pop_front(deq);
	val_2 = pop_front(deq);
	if (!push_front(deq, val_1))
		throw_error(all);
	if (!push_front(deq, val_2))
		throw_error(all);
	if (!add_op_list(all->op_list, op))
		throw_error(all);
}

void	push(char to, t_all *all)
{
	int		val;
	char	*op;
	t_deque	*deq_from;
	t_deque	*deq_to;

	if (to == 'a')
	{
		deq_from = all->deq_B;
		deq_to = all->deq_A;
		op = "pa";
	}
	else
	{
		deq_from = all->deq_A;
		deq_to = all->deq_B;
		op = "pb";
	}
	if (deq_is_empty(deq_from))
		return ;
	val = pop_front(deq_from);
	if (!push_front(deq_to, val))
		throw_error(all);
	if (!add_op_list(all->op_list, op))
		throw_error(all);
}

void	rotate(char name, t_all *all)
{
	int		val;
	char	*op;
	t_deque	*deq;

	if (name == 'a')
	{
		deq = all->deq_A;
		op = "ra";
	}
	else
	{
		deq = all->deq_B;
		op = "rb";
	}
	if (deq_is_empty(deq))
		return ;
	val = pop_front(deq);
	if (!push_back(deq, val))
		throw_error(all);
	if (!add_op_list(all->op_list, op))
		throw_error(all);
}

void	r_rotate(char name, t_all *all)
{
	int		val;
	char	*op;
	t_deque	*deq;

	if (name == 'a')
	{
		deq = all->deq_A;
		op = "rra";
	}
	else
	{
		deq = all->deq_B;
		op = "rrb";
	}
	if (deq_is_empty(deq))
		return ;
	val = pop_back(deq);
	if (!push_front(deq, val))
		throw_error(all);
	if (!add_op_list(all->op_list, op))
		throw_error(all);
}

void	print_op(t_op *op_list)
{
	t_list	*cur;

	cur = op_list->head;
	while (cur)
	{
		ft_putstr_fd(cur->op, 1);
		cur = cur->next;
	}
}
