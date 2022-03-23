/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:51:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/23 20:42:27 by jinyoo           ###   ########.fr       */
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
	t_inform inform;

	if (argc == 5 || argc == 6)
	{
		init_inform(&inform, argv, argc);
		printf("%d %d %d %d %d", inform.numOfPhils, inform.timeToDie, inform.timeToEat, inform.timeToSleep, inform.numOfMustEat);
	}
	else
		printf("Usage: ./philo (num_p) (t_d) (t_e) (t_s) [num_m_e]\n");
	return (0);
}
