/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:26:00 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/29 16:47:23 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		eat(t_phil *philo)
{
	if (!print_state(philo, EATING))
		return (0); // 오류
	philo->numOfEat += 1;
	if (philo->inform->numOfMustEat == philo->numOfEat)
	{
		if (print_state(philo, FULL))
			return (0);
		else
			return (0); // 오류
	}
	return (1);
}