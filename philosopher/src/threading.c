/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:55:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/01 21:47:04 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	putdown_forks(t_phil *philo)
{
	if (!check_exit(philo))
		return ;
	pthread_mutex_unlock(&philo->inform->fork_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->inform->fork_mutex[philo->right_fork]);
}

static void	pickup_forks(t_phil *philo)
{
	if (!check_exit(philo))
		return ;
	pthread_mutex_lock(&philo->inform->fork_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->inform->fork_mutex[philo->right_fork]);
	print_state(philo, PICKUP);
	print_state(philo, PICKUP);
}

void	*monitoring(void *phil)
{
	t_phil		*philo;
	long long	now;

	philo = (t_phil *)phil;
	time_travel(philo, 0, philo->inform->timeToDie - 10);
	while (check_exit(philo))
	{
		get_time(&now);
		if (now - philo->time > (long long)philo->inform->timeToDie)
		{
			print_state(philo, DEAD);
			philo->inform->isDie = DEAD;
			break; 
		}
	}
	return (NULL);
}

void	*dining_phils(void *phil)
{
	t_phil	*philo;

	philo = (t_phil *)phil;
	get_time(&philo->time);
	while (check_exit(philo))
	{
		pickup_forks(philo);
		p_eat(philo);
		putdown_forks(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}