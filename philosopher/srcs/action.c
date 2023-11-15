/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:10:00 by jinyoo            #+#    #+#             */
/*   Updated: 2023/11/15 13:19:18 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	thinking(t_philo *philo)
{
	t_param	*param;

	param = philo->param;
	return (print_state(philo, param, THINKING, 0));
}

int	sleeping(t_philo *philo)
{
	t_param		*param;

	param = philo->param;
	if (print_state(philo, param, SLEEPING, 0))
		return (1);
	throw_time(philo, get_now(), param->sleep_time);
	return (0);
}

static int	take_fork(t_philo *philo, t_param *param)
{
	if (check_die_mutex(param))
		return (1);
	pthread_mutex_lock(param->fork + philo->l_fork);
	if (print_state(philo, param, TAKE, 0))
	{
		pthread_mutex_unlock(param->fork + philo->l_fork);
		return (1);
	}
	if (check_die_mutex(param))
		return (1);
	pthread_mutex_lock(param->fork + philo->r_fork);
	if (print_state(philo, param, TAKE, FORK))
	{
		pthread_mutex_unlock(param->fork + philo->r_fork);
		return (1);
	}
	return (0);
}

int	eating(t_philo *philo)
{
	t_param		*param;

	param = philo->param;
	if (take_fork(philo, param))
		return (1);
	if (print_state(philo, param, EATING, EAT))
		return (1);
	throw_time(philo, philo->last_eat_time, param->eat_time);
	if (check_die_mutex(param))
		return (1);
	pthread_mutex_unlock(param->fork + philo->l_fork);
	pthread_mutex_unlock(param->fork + philo->r_fork);
	return (0);
}

void	*threading(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	while (1)
	{
		if (check_die_mutex(philo->param))
			return (NULL);
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
