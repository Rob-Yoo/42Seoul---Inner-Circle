/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:55:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/04 20:51:51 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	putdown_forks(t_phil *philo, t_mutex *forks)
{
	pthread_mutex_unlock(&forks[philo->left_fork]);
	pthread_mutex_unlock(&forks[philo->right_fork]);
	if (philo->me + 1 == philo->inform->num_phils)
		philo->inform->state[0] = 1;
	else
		philo->inform->state[philo->me + 1] = 1;
	if (!phils_guide(philo))
		return ;
}

static void	pickup_forks(t_phil *philo, t_mutex *forks)
{
	if (!phils_guide(philo))
		return ;
	philo->inform->state[philo->me] = 0;
	pthread_mutex_lock(&forks[philo->left_fork]);
	print_state(philo, PICKUP);
	pthread_mutex_lock(&forks[philo->right_fork]);
	print_state(philo, PICKUP);
}

void	*monitoring(void *param)
{
	t_phil		*phils;
	t_inform	*inform;
	long long	now;
	int			i;

	phils = (t_phil *)param;
	inform = phils[0].inform;
	time_travel(0, inform->tim_die - 10);
	while (TRUE)
	{
		if (inform->die || inform->fin)
			break ;
		i = -1;
		get_time(&now);
		while (++i < inform->num_phils)
			if (now - inform->time[i] > (long long)inform->tim_die)
				print_state(&phils[i], DEAD);
	}
	return (NULL);
}

void	*dining_phils(void *phil)
{
	t_phil	*philo;
	int		num_phils;
	int		*state;
	t_mutex	*forks;

	philo = (t_phil *)phil;
	num_phils = philo->inform->num_phils;
	state = philo->inform->state;
	forks = philo->inform->fork_mutex;
	get_time(&philo->inform->time[philo->me]);
	while (phils_guide(philo))
	{
		if (state[philo->me])
		{
			pickup_forks(philo, forks);
			p_eat(philo);
			putdown_forks(philo, forks);
			p_sleep(philo);
			p_think(philo);
		}
		usleep(100);
	}
	return (NULL);
}
