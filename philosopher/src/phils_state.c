/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:26:00 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/30 16:16:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		eat(t_phil *philo)
{
	print_state(philo, EATING);
	philo->numOfEat += 1;
	if (philo->inform->numOfMustEat == philo->numOfEat)
	{
		print_state(philo, FULL);
		pthread_mutex_unlock(&philo->inform->main_lock);
	}
}