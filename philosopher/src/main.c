/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:51:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/23 17:06:01 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	if (argc == 5 || argc == 6)
	{
		(void)argv;
	}
	else
	{
		printf("Usage: ./philo (number_of_philosophers) (time_to_die)");
		printf("(time_to_eat) (time_to_sleep) [number_of_times_each_philosopher_must_eat]");
	}
	return (0);
}
