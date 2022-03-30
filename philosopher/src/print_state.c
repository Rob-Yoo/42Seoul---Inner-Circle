/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:36:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/30 22:14:42 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_phil *philo, int state)
{
	long long	now;
	
	pthread_mutex_lock(&philo->inform->print_lock);
	get_time(&now);
	ft_putnbr(now - philo->inform->start);
	if (state == FINISH)
		ft_putendl("\tFinish!!!!");
	else
	{
		ft_putstr("\t");
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
	if (!(state == DEAD) && !(state == FINISH))
		pthread_mutex_unlock(&philo->inform->print_lock);
}