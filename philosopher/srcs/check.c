/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:20:11 by jinyoo            #+#    #+#             */
/*   Updated: 2023/11/15 13:20:24 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die_mutex(t_param *param)
{
	if (!param->print || !param->fork || !param->check)
		return (1);
	pthread_mutex_lock(param->check);
	if (param->die_state)
	{
		pthread_mutex_unlock(param->check);
		return (1);
	}
	pthread_mutex_unlock(param->check);
	return (0);
}
