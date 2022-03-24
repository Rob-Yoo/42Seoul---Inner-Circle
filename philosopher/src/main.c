/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:51:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/24 17:15:02 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_inform(t_inform *inform, char *argv[], int argc)
{
	inform->numOfPhils = ft_atoi(argv[1]);
	inform->timeToDie = ft_atoi(argv[2]);
	inform->timeToEat = ft_atoi(argv[3]);
	inform->timeToSleep = ft_atoi(argv[4]);
	if (argc == 6)
		inform->numOfMustEat = ft_atoi(argv[5]);
	pthread_mutex_init(&inform->mutex, NULL);
	inform->state = (int *)malloc(sizeof(int) * inform->numOfPhils);
}

static void	init_phils(t_inform inform, t_phil *phils)
{
	int	i;

	i = 0;
	while (i < inform.numOfPhils)
	{
		phils[i].inform = inform;
		phils[i].whoAmI = i + 1;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_inform	inform;
	t_phil		*phils;
	int			i;
	pthread_t	tid;

	if (argc == 5 || argc == 6)
	{
		i = -1;
		init_inform(&inform, argv, argc);
		phils = (t_phil *)malloc(sizeof(t_phil) * inform.numOfPhils);
		init_phils(inform, phils);
		while (++i < inform.numOfPhils)
			pthread_create(&tid, NULL, philosophers, (void *)&phils[i]);
		while (i--)
			pthread_join(tid, NULL);
	}
	else
		printf("Usage: ./philo (num_p) (t_d) (t_e) (t_s) [num_m_e]\n");
	return (0);
}
