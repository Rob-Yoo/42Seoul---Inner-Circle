/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:55:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/30 18:17:29 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	putdown_forks(t_phil *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	pthread_mutex_unlock(&philo->inform->fork_mutex[left_fork]);
	pthread_mutex_unlock(&philo->inform->fork_mutex[right_fork]);
}

static void	pickup_forks(t_phil *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	pthread_mutex_lock(&philo->inform->fork_mutex[left_fork]);
	pthread_mutex_lock(&philo->inform->fork_mutex[right_fork]);
	print_state(philo, PICKUP);
	print_state(philo, PICKUP);
}

void	*dining_phils(void *phil)
{
	t_phil	*philo;

	philo = (t_phil *)phil;
	if (philo->me % 2)
		time_travel(0, 100);
	get_time(&philo->time);
	while (TRUE)
	{
		pickup_forks(philo);
		p_eat(philo);
		putdown_forks(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}