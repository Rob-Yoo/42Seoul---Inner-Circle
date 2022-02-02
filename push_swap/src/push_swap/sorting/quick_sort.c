/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 03:11:57 by jinyoo            #+#    #+#             */
/*   Updated: 2022/02/03 02:03:13 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swp(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	quick_sort(int arr[], int pivot, int end)
{
	int	left;
	int	right;

	if (pivot >= end)
		return ;
	left = pivot + 1;
	right = end;
	while (left <= right)
	{
		while (left <= end && arr[left] <= arr[pivot])
			left++;
		while (right > pivot && arr[pivot] <= arr[right])
			right--;
		if (left > right)
			swp(&arr[pivot], &arr[right]);
		else
			swp(&arr[left], &arr[right]);
	}
	quick_sort(arr, pivot, right - 1);
	quick_sort(arr, right + 1, end);
}

int	find_pivot(t_deque *deq, int size)
{
	int		pivot;
	int		arr[size];
	int		i;
	t_dlist	*cur;

	i = 0;
	cur = deq->head;
	while (i < size)
	{
		arr[i++] = cur->value;
		cur = cur->next;
	}
	quick_sort(arr, 0, size - 1);
	pivot = arr[size / 2];
	return (pivot);
}

int	is_ascending(t_deque *deq_A, int chunk_size)
{
	t_dlist	*cur;
	int		i;

	cur = deq_A->head;
	i = 0;
	while (++i < chunk_size)
	{
		if (cur->next)
		{
			if (cur->value > cur->next->value)
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	is_descending(t_deque *deq_B, int chunk_size)
{
	t_dlist	*cur;
	int		i;

	cur = deq_B->head;
	i = 0;
	while (++i < chunk_size)
	{
		if (cur->next)
		{
			if (cur->value < cur->next->value)
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}
