/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:26:00 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/01 21:47:31 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_exit(t_phil *philo)
{
	if (philo->inform->isDie || philo->inform->isFin)
		return (0);
	return (1);
}

void	p_eat(t_phil *philo)
{
	if (!check_exit(philo))
		return ;
	print_state(philo, EATING);
	get_time(&philo->time);
	philo->numOfEat += 1;
	time_travel(philo, philo->time, philo->inform->timeToEat);
	if (philo->inform->numOfMustEat && \
	philo->inform->numOfMustEat == philo->numOfEat)
	{
		philo->inform->numOfFinishingEat += 1;
		if (philo->inform->numOfFinishingEat >= philo->inform->numOfPhils)
		{
			print_state(philo, FINISH);
			philo->inform->isFin = FINISH;
		}
	}
}

void	p_sleep(t_phil *philo)
{
	if (!check_exit(philo))
		return ;
	print_state(philo, SLEEPING);
	time_travel(philo, 0, philo->inform->timeToSleep);
}

void	p_think(t_phil *philo)
{
	if (!check_exit(philo))
		return ;
	print_state(philo, THINKING);
}