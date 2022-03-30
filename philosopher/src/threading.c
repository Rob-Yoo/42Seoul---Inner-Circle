/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:55:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/30 11:15:21 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	putdown_forks(t_phil *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->left_fork;
	right_fork = philo->right_fork;
	if (pthread_mutex_unlock(&philo->inform->fork_mutex[left_fork]) || \
	pthread_mutex_unlock(&philo->inform->fork_mutex[right_fork])
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
	while (TRUE)
	{
		pickup_forks(philo);
		eat(philo);
		putdown_forks(philo);
		// philo_sleep(philo);
		// philo_think(philo);
	}
	return (NULL);
}