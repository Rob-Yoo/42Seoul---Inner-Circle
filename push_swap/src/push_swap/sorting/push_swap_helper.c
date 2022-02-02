/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 04:12:07 by jinyoo            #+#    #+#             */
/*   Updated: 2022/02/03 03:00:03 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_all *all, int cnt, int sign, char where)
{
	if (where == 'a')
	{
		if (sign == SECOND_RECUR)
			while (cnt--)
				r_rotate('a', all);
	}
	else
	{
		if (sign == SECOND_RECUR || sign == FIRST_RECUR)
			while (cnt--)
				r_rotate('b', all);
	}
}

static int	handle_descending(t_all *all)
{
	int cnt;

	if (is_descending(all->deq_B, all->deq_B->size))
	{
		cnt = all->deq_B->size;
		while (cnt--)
			push('a', all);
		return (1);
	}
	return (0);
}

int	make_B_chunk(t_all *all, int pivot, int chunk_size, int sign)
{
	int	r_cnt;
	int	p_cnt;
	t_dlist *head;

	r_cnt = 0;
	p_cnt = 0;
	while (p_cnt != chunk_size / 2)
	{
		if (is_ascending(all->deq_A, all->deq_A->size) && p_cnt == 0)
			return (0) ;
		head = all->deq_A->head;
		if (head->value < pivot)
		{
			push('b', all);
			p_cnt++;
		}
		else
		{
			rotate('a', all);
			r_cnt++;
		}
	}
	reverse_rotate(all, r_cnt, sign, 'a');
	return (p_cnt);
}

int	make_A_chunk(t_all *all, int pivot, int chunk_size, int sign)
{
	int	p_cnt;
	int	r_cnt;
	int	A_chunk_size;

	if (handle_descending(all))
		return (0);
	p_cnt = 0;
	r_cnt = 0;
	A_chunk_size = chunk_size - (chunk_size / 2 + 1);
	while (p_cnt != A_chunk_size)
	{
		if (all->deq_B->head->value > pivot)
		{
			push('a', all);
			p_cnt++;
		}
		else
		{
			rotate('b', all);
			r_cnt++;
		}
	}
	reverse_rotate(all, r_cnt, sign, 'b');
	return (p_cnt);
}
