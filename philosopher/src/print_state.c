/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:36:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/30 16:16:51 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_phil *philo, int state)
{
	pthread_mutex_lock(&philo->inform->print_lock);
	if (state == FULL)
		ft_putstr("Finish!!!!");
	else
	{
		ft_putnbr(philo->me + 1);
		if (state == PICKUP)
			ft_putstr(" has taken a fork");
		else if (state == EATING)
			ft_putstr(" is eating");
	}
	pthread_mutex_unlock(&philo->inform->print_lock);
}