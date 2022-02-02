/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_push_swap.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 02:57:52 by jinyoo            #+#    #+#             */
/*   Updated: 2022/02/03 04:01:29 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(int arr[], char where, int size)
{
	int	i;

	i = -1;
	if (where == 'a')
	{
		while (++i < size - 1)
			if (arr[i] > arr[i + 1])
				return (0);
	}
	else
	{
		while (++i < size - 1)
			if (arr[i] < arr[i + 1])
				return (0);
	}
	return (1);
}

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

void	if_swap(t_all *all, char where, int chunk_size)
{
	int	arr[chunk_size];
	int	i;
	t_dlist *cur;

	i = 0;
	if (where == 'a')
		cur = all->deq_A->head;
	else
		cur = all->deq_B->head;
	while (i < chunk_size)
	{
		arr[i++] = cur->value;
		cur = cur->next;
	}
	swp(&arr[0], &arr[1]);
	if (where == 'a')
	{
		if (is_sorted(arr, 'a', chunk_size))
			swap('a', all);
	}
	else
	{
		if (is_sorted(arr, 'b', chunk_size))
			swap('b', all);
	}
}
