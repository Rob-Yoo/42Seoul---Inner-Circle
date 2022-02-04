/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_push_swap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 02:57:52 by jinyoo            #+#    #+#             */
/*   Updated: 2022/02/04 14:20:56 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_three_arg_A(t_all *all, int mid_val)
{
	t_dlist	*head;

	head = all->deq_A->head;
	if (is_ascending(all->deq_A, all->deq_A->size))
		return ;
	if (head->value == mid_val)
	{
		if (head->value < head->next->value)
			r_rotate('a', all);
		else
			swap('a', all);
	}
	else if (head->value > mid_val)
	{
		rotate('a', all);
		if (!is_ascending(all->deq_A, all->deq_A->size))
			swap('a', all);
	}
	else
	{
		push('b', all);
		swap('a', all);
		push('a', all);
	}
}

void	ps_three_arg_B(t_all *all, int mid_val)
{
	t_dlist	*head;

	head = all->deq_B->head;
	if (is_descending(all->deq_B, 3))
		return ;
	if (head->value == mid_val)
	{
		if (head->value < head->next->value)
			swap('b', all);
		else
			r_rotate('b', all);
	}
	else if (head->value > mid_val)
	{
		r_rotate('b', all);
		swap('b', all);
	}
	else
	{
		rotate('b', all);
		if (!is_descending(all->deq_B, 3))
			swap('b', all);
	}
}
