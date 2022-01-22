/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:43:02 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/22 17:39:44 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init(t_deque *deq_A, t_deque *deq_B, t_op *op_list, t_all *all)
{
	deq_A->head = NULL;
	deq_A->tail = NULL;
	deq_A->size = 0;
	deq_B->head = NULL;
	deq_B->tail = NULL;
	deq_B->size = 0;
	op_list->head = NULL;
	op_list->tail = NULL;
	all->deq_A = deq_A;
	all->deq_B = deq_B;
	all->op_list = op_list;
}

static int	ft_atoi(const char *str, t_all *all)
{
	int					sign;
	unsigned long long	num;
	int					i;

	i = 0;
	num = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			num = 10 * num + str[i++] - '0';
		else
			throw_error(all);
	}
	if ((sign == -1 && num > 2147483648) || num > 2147483647)
		throw_error(all);
	return (sign * (int)num);
}

static int	set_A(char *arg, t_all *all)
{
	int		data;
	t_dlist	*tail;
	int		flag;

	data = ft_atoi(arg, all);
	tail = all->deq_A->tail;
	flag = 0;
	if (!find_duplicate(data, all->deq_A->head))
		throw_error(all);
	if (tail)
		if (tail->value > data)
			flag = 1;
	push_back(all->deq_A, data);
	return (flag);
}

int	main(int argc, char *argv[])
{
	t_all	all;
	t_deque	deq_A;
	t_deque	deq_B;
	t_op	op_list;
	int		flag;

	if (argc > 1)
	{
		flag = 0;
		init(&deq_A, &deq_B, &op_list, &all);
		while (--argc)
			if (set_A(*(++argv), &all))
				flag = 1;
		if (flag)
		{
			init_push_swap(&all);
			print_op(&op_list);
			free_all(&all);
		}
		else
			free_all(&all);
	}
	return (0);
}
