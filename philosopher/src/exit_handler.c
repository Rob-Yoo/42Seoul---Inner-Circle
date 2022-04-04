/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:52:24 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/04 21:45:36 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	throw_error(t_phil *phils)
{
	write(2, "Error\n", 6);
	ft_exit(phils);
	return (0);
}

int	ft_exit(t_phil *phils)
{
	t_inform	*inform;
	int			i;

	i = -1;
	inform = phils->inform;
	if (inform->state)
		free(inform->state);
	if (inform->time)
		free(inform->time);
	if (inform->fork_mutex)
	{
		while (++i < inform->num_phils)
			pthread_mutex_destroy(&inform->fork_mutex[i]);
		free(inform->fork_mutex);
	}
	pthread_mutex_destroy(&inform->print_lock);
	pthread_mutex_destroy(&inform->fin_lock);
	free(phils);
	return (0);
}
