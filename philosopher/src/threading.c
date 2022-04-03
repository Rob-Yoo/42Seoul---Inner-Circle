/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:55:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/03 22:43:33 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	putdown_forks(t_phil *philo, t_mutex *forks)
{
	pthread_mutex_unlock(&forks[philo->left_fork]);
	pthread_mutex_unlock(&forks[philo->right_fork]);
	if (!phils_guide(philo))
		return ;
}

static void	pickup_forks(t_phil *philo, t_mutex *forks, int *state, int num)
{
	if (!phils_guide(philo))
		return ;
	pthread_mutex_lock(&forks[philo->left_fork]);
	pthread_mutex_lock(&forks[philo->right_fork]);
	print_state(philo, PICKUP);
	print_state(philo, PICKUP);
	if (philo->me + 1 == num)
		state[0] = 1;
	else
		state[philo->me + 1] = 1;
	state[philo->me] = 0;
}

void	*monitoring(void *phil)
{
	t_phil		*philo;
	long long	now;

	philo = (t_phil *)phil;
	time_travel(philo, 0, philo->inform->timeToDie - 10);
	while (phils_guide(philo))
	{
		get_time(&now);
		if (now - philo->time > (long long)philo->inform->timeToDie)
			print_state(philo, DEAD);
	}
	return (NULL);
}

void	*dining_phils(void *phil)
{
	t_phil	*philo;
	int		numOfPhils;
	int		*state;
	t_mutex	*forks;

	philo = (t_phil *)phil;
	numOfPhils = philo->inform->numOfPhils;
	state = philo->inform->state;
	forks = philo->inform->fork_mutex;
	get_time(&philo->time);
	while (phils_guide(philo))
	{
		if (state[philo->me]) 
		{
			pickup_forks(philo, forks, state, numOfPhils);
			p_eat(philo);
			putdown_forks(philo, forks);
			p_sleep(philo);
			p_think(philo);
		}
	}
	return (NULL);
}
