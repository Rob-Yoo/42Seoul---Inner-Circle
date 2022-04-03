/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:26:00 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/03 22:00:58 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phils_guide(t_phil *philo)
{	
	t_inform	*inform;

	inform = philo->inform;
	if (inform->isDie || inform->isFin)
		return (0);
	return (1);
}

void	p_eat(t_phil *philo)
{
	t_inform	*inform;

	inform = philo->inform;
	if (!phils_guide(philo))
		return ;
	print_state(philo, EATING);
	philo->numOfEat += 1;
	get_time(&philo->time);
	time_travel(philo, philo->time, inform->timeToEat);
	if (inform->numOfMustEat && inform->numOfMustEat == philo->numOfEat)
	{
		inform->numOfFinishingEat += 1;
		if (inform->numOfFinishingEat >= inform->numOfPhils)
			print_state(philo, FINISH);
	}
}

void	p_sleep(t_phil *philo)
{
	if (!phils_guide(philo))
		return ;
	print_state(philo, SLEEPING);
	time_travel(philo, 0, philo->inform->timeToSleep);
}

void	p_think(t_phil *philo)
{
	if (!phils_guide(philo))
		return ;
	print_state(philo, THINKING);
}
