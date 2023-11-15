/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 20:34:02 by jinyoo            #+#    #+#             */
/*   Updated: 2023/11/15 13:21:04 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

int	time_watch(long long start)
{
	long long	now;

	now = get_now();
	return ((int)(now - start));
}

void	throw_time(t_philo *philo, long long start, int end)
{
	t_param		*param;

	param = philo->param;
	while (time_watch(start) < end)
		usleep(200);
}
