/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:31:03 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/25 20:30:46 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

static void	ps_three_arg(t_all *all)
{
	int		val;

	val = all->deq_A->head->value;
	if (val == 2)
	{
		rotate('a', all);
		if (all->deq_A->head->next->value == 0)
			swap('a', all);
	}
	else if (val == 1)
	{
		if (all->deq_A->head->next->value == 0)
			swap('a', all);
		else
			r_rotate('a', all);
	}
	else
	{
		push('b', all);
		swap('a', all);
		push('a', all);
	}
}

void	init_push_swap(t_all *all)
{
	int	size;

	size = all->deq_A->size;
	if (size == 2)
		rotate('a', all);
	else if (size == 3)
		ps_three_arg(all);
}