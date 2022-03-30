/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:26:00 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/30 22:09:30 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p_eat(t_phil *philo)
{
	print_state(philo, EATING);
	get_time(&philo->time);
	philo->numOfEat += 1;
	time_travel(philo->time, philo->inform->timeToEat);
	if (philo->inform->numOfMustEat && \
	philo->inform->numOfMustEat == philo->numOfEat)
	{
		philo->inform->numOfFinishingEat += 1;
		if (philo->inform->numOfFinishingEat >= philo->inform->numOfPhils)
		{
			print_state(philo, FINISH);
			pthread_mutex_unlock(&philo->inform->main_lock);
		}
	}
}

void	p_sleep(t_phil *philo)
{
	print_state(philo, SLEEPING);
	time_travel(0, philo->inform->timeToSleep);
}

void	p_think(t_phil *philo)
{
	print_state(philo, THINKING);
}