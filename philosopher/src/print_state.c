/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:36:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/01 21:53:23 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_phil *philo, int state)
{
	long long	now;

	pthread_mutex_lock(&philo->inform->print_lock);
	if (check_exit(philo))
	{
		if (state == FINISH)
			ft_putendl("Finish!!!!");
		else
		{
			get_time(&now);
			ft_putnbr(now - philo->inform->start);
			ft_putstr("ms\t");
			ft_putnbr(philo->me + 1);
			if (state == PICKUP)
				ft_putendl(" has taken a fork");
			else if (state == EATING)
				ft_putendl(" is eating");
			else if (state == SLEEPING)
				ft_putendl(" is sleeping");
			else if (state == THINKING)
				ft_putendl(" is thinking");
			else if (state == DEAD)
				ft_putendl(" died");
		}
	}
	pthread_mutex_unlock(&philo->inform->print_lock);
}
