/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:51:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/04 21:42:35 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_helper(t_inform *inform, char *argv[], int argc)
{
	inform->num_phils = ft_atoi(argv[1]);
	inform->tim_die = ft_atoi(argv[2]);
	inform->tim_eat = ft_atoi(argv[3]);
	inform->time_sleep = ft_atoi(argv[4]);
	inform->die = 0;
	inform->fin = 0;
	if (argc == 6)
	{
		inform->num_must_eat = ft_atoi(argv[5]);
		inform->num_fin_eat = 0;
	}
}

static int	init_inform(t_inform *inform, char *argv[], int argc)
{
	int	i;

	init_helper(inform, argv, argc);
	inform->state = (int *)malloc(sizeof(int) * inform->num_phils);
	if (!inform->state)
		return (0);
	inform->time = (long long *)malloc(sizeof(long long) * \
	inform->num_phils);
	if (!inform->time)
		return (0);
	inform->fork_mutex = (t_mutex *)malloc(sizeof(t_mutex) * \
	inform->num_phils);
	if (!inform->fork_mutex)
		return (0);
	i = -1;
	while (++i < inform->num_phils)
		if (pthread_mutex_init(&inform->fork_mutex[i], NULL))
			return (0);
	if (pthread_mutex_init(&inform->print_lock, NULL) || \
	pthread_mutex_init(&inform->fin_lock, NULL))
		return (0);
	return (1);
}

static void	init_phils(t_inform *inform, t_phil *phils)
{
	int	i;

	i = -1;
	while (++i < inform->num_phils)
	{
		if (i % 2 || i == inform->num_phils - 1)
			inform->state[i] = 0;
		else
			inform->state[i] = 1;
	}
	i = 0;
	while (i < inform->num_phils)
	{
		phils[i].inform = inform;
		phils[i].me = i;
		phils[i].left_fork = i;
		phils[i].right_fork = (i + 1) % inform->num_phils;
		phils[i].num_eat = 0;
		i++;
	}
}

static int	make_phils_to_sit(t_inform *inform, t_phil *phils, int num_phils)
{
	int	i;

	i = -1;
	get_time(&inform->start);
	while (++i < num_phils)
	{
		if (pthread_create(&phils[i].dining_tid, NULL, dining_phils, \
		(void *)&phils[i]))
			return (0);
		if (i == num_phils - 1)
			if (pthread_create(&inform->monitoring_tid, NULL, monitoring, \
			(void *)phils))
				return (0);
	}
	i = -1;
	while (++i < num_phils)
	{
		if (pthread_join(phils[i].dining_tid, NULL))
			return (0);
		if (i == 0)
			if (pthread_join(inform->monitoring_tid, NULL))
				return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_inform	inform;
	t_phil		*phils;

	if (argc == 5 || argc == 6)
	{
		phils = (t_phil *)malloc(sizeof(t_phil) * ft_atoi(argv[1]));
		if (!phils || !init_inform(&inform, argv, argc))
			return (throw_error(phils));
		init_phils(&inform, phils);
		if (!make_phils_to_sit(&inform, phils, inform.num_phils))
			return (throw_error(phils));
		ft_exit(phils);
	}
	return (0);
}
