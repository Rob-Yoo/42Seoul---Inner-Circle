/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:51:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/01 21:42:00 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_inform(t_inform *inform, char *argv[], int argc)
{
	int	i;

	inform->numOfPhils = ft_atoi(argv[1]);
	inform->timeToDie = ft_atoi(argv[2]);
	inform->timeToEat = ft_atoi(argv[3]);
	inform->timeToSleep = ft_atoi(argv[4]);
	inform->isDie = 0;
	inform->isFin = 0;
	if (argc == 6)
	{
		inform->numOfMustEat = ft_atoi(argv[5]);
		inform->numOfFinishingEat = 0;
	}
	inform->fork_mutex = (mutex *)malloc(sizeof(mutex) * inform->numOfPhils);
	if (!inform->fork_mutex)
		return (0);
	i = -1;
	while (++i < inform->numOfPhils)
		if (pthread_mutex_init(&inform->fork_mutex[i], NULL))
			return (0);
	if (pthread_mutex_init(&inform->print_lock, NULL) || \
	pthread_mutex_init(&inform->main_lock, NULL))
		return (0);
	return (1);
}

static void	init_phils(t_inform *inform, t_phil *phils)
{
	int	i;

	i = 0;
	while (i < inform->numOfPhils)
	{
		phils[i].inform = inform;
		phils[i].me = i;
		phils[i].left_fork = i;
		phils[i].right_fork = (i + 1) % inform->numOfPhils;
		phils[i].numOfEat = 0;
		i++;
	}
}

static int	make_phils_to_sit(t_inform *inform, t_phil *phils, int numOfPhils)
{
	int	i;

	i = 0;
	get_time(&inform->start);
	while (i < numOfPhils)
	{
		if (pthread_create(&phils[i].dining_tid, NULL, dining_phils, \
		(void *)&phils[i]))
			return (0);
		if (pthread_create(&phils[i].monitoring_tid, NULL, monitoring, \
		(void *)&phils[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < numOfPhils)
	{
		if (pthread_join(phils[i].dining_tid, NULL))
			return (0);
		if (pthread_join(phils[i].monitoring_tid, NULL))
			return (0);
		i++;
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
		if (!make_phils_to_sit(&inform, phils, inform.numOfPhils))
			return (throw_error(phils));
	}
	return (0);
}
