/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:51:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/23 20:56:52 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_inform(t_inform *inform, char *argv[], int argc)
{
	inform->numOfPhils = ft_atoi(argv[1]);
	inform->timeToDie = ft_atoi(argv[2]);
	inform->timeToEat = ft_atoi(argv[3]);
	inform->timeToSleep = ft_atoi(argv[4]);
	if (argc == 6)
		inform->numOfMustEat = ft_atoi(argv[5]);
}

int	main(int argc, char *argv[])
{
	t_inform	inform;
	int			i;
	pthread_t	tid;

	if (argc == 5 || argc == 6)
	{
		i = -1;
		init_inform(&inform, argv, argc);
		while (++i < inform.numOfPhils)
			pthread_create(&tid, NULL, philosophers, (void *)&inform);
		while (i--)
			pthread_join(tid, NULL);
	}
	else
		printf("Usage: ./philo (num_p) (t_d) (t_e) (t_s) [num_m_e]\n");
	return (0);
}
