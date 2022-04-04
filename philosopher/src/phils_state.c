/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:26:00 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/04 18:16:43 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phils_guide(t_phil *philo)
{	
	t_inform	*inform;

	inform = philo->inform;
	if (inform->die || inform->fin)
		return (0);
	return (1);
}

static void	check_finish(t_phil *philo, t_inform *inform)
{
	if (inform->num_must_eat && inform->num_must_eat == philo->num_eat)
	{
		inform->num_fin_eat += 1;
		if (inform->num_fin_eat >= inform->num_phils)
			print_state(philo, FINISH);
	}
}

void	p_eat(t_phil *philo)
{
	t_inform	*inform;

	inform = philo->inform;
	if (!phils_guide(philo))
		return ;
	print_state(philo, EATING);
	philo->num_eat += 1;
	get_time(&inform->time[philo->me]);
	time_travel(inform->time[philo->me], inform->tim_eat);
	if (philo->me + 1 == inform->num_phils)
		inform->state[0] = 1;
	else
		inform->state[philo->me + 1] = 1;
	inform->state[philo->me] = 0;
	check_finish(philo, inform);
}

void	p_sleep(t_phil *philo)
{
	if (!phils_guide(philo))
		return ;
	print_state(philo, SLEEPING);
	time_travel(0, philo->inform->time_sleep);
}

void	p_think(t_phil *philo)
{
	if (!phils_guide(philo))
		return ;
	print_state(philo, THINKING);
}
