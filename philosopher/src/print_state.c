/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:36:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/29 16:44:08 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state(t_phil *philo, int state)
{
	if (pthread_mutex_lock(&philo->inform->print_lock))
		return (0);
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
	if (pthread_mutex_unlock(&philo->inform->print_lock))
		return (0);
	return (1);
}