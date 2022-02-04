/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:31:03 by jinyoo            #+#    #+#             */
/*   Updated: 2022/02/04 14:33:00 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	B_to_A(t_all *all, int sign, int B_chunk_size)
{
	int	pivot;
	int	A_chunk_size;

	if (B_chunk_size <= 2 || all->deq_B->size == 3)
	{
		if (all->deq_B->size == 3)
			ps_three_arg_B(all, find_pivot(all, 'b', 3));
		if (!is_descending(all->deq_B, B_chunk_size))
			swap('b', all);
		while (B_chunk_size--)
			push('a', all);
	}
	else
	{
		pivot = find_pivot(all, 'b', B_chunk_size);
		A_chunk_size = make_A_chunk(all, pivot, B_chunk_size, sign);
		if (!A_chunk_size)
			return ;
		if (!is_ascending(all->deq_A, A_chunk_size))
			A_to_B(all, SECOND_RECUR, A_chunk_size);
		if (sign == INIT_RECUR)
			B_to_A(all, INIT_RECUR, B_chunk_size - A_chunk_size);
		else
			B_to_A(all, SECOND_RECUR, B_chunk_size - A_chunk_size);
	}
}

void	A_to_B(t_all *all, int sign, int A_chunk_size)
{
	int	pivot;
	int	new_A_chunk_size;
	int	B_chunk_size;

	if (A_chunk_size <= 2 || all->deq_A->size == 3)
	{
		if (all->deq_A->size == 3)
			ps_three_arg_A(all, find_pivot(all, 'a', 3));
		if (!is_ascending(all->deq_A, A_chunk_size))
			swap('a', all);
	}
	else
	{
		pivot = find_pivot(all, 'a', A_chunk_size);
		B_chunk_size = make_B_chunk(all, pivot, A_chunk_size, sign);
		if (!B_chunk_size)
			return ;
		new_A_chunk_size = A_chunk_size - B_chunk_size;
		if (sign == SECOND_RECUR)
			A_to_B(all, SECOND_RECUR, new_A_chunk_size);
		else
			A_to_B(all, FIRST_RECUR, new_A_chunk_size);
		if (all->deq_B->size > 0)
			B_to_A(all, sign, B_chunk_size);
	}
}

void	init_push_swap(t_all *all)
{
	int	size;

	size = all->deq_A->size;
	if (size == 2)
		swap('a', all);
	else if (size == 3)
		ps_three_arg_A(all, find_pivot(all, 'a', 3));
	else
		A_to_B(all, INIT_RECUR, all->deq_A->size);
}
