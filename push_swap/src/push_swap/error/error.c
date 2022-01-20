/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:33:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/20 16:04:42 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_duplicate(int value, t_dlist *head)
{
	t_dlist	*cur;

	cur = head;
	while (cur)
	{
		if (cur->value == value)
			return (0);
		else
			cur = cur->next;
	}
	return (1);
}

void	free_all(t_all *all)
{
	t_list	*op_node;
	t_dlist	*deq_node;

	deq_node = all->deq_A->head;
	while (deq_node)
	{
		all->deq_A->head = deq_node->next;
		free(deq_node);
		deq_node = all->deq_A->head;
	}
	deq_node = all->deq_B->head;
	while (deq_node)
	{
		all->deq_B->head = deq_node->next;
		free(deq_node);
		deq_node = all->deq_B->head;
	}
	op_node = all->op_list->head;
	while (op_node)
	{
		all->op_list->head = op_node->next;
		free(op_node);
		op_node = all->op_list->head;
	}
}

void	throw_error(t_all *all)
{
	free_all(all);
	ft_putstr_fd("Error\n", 1);
	exit(1);
}
