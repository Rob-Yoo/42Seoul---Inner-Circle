/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:21:30 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/01 21:45:03 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_time(long long *val)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	*val = (long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	time_travel(t_phil *philo, long long start, long long time)
{
	long long	now;

	if (!start)
		get_time(&start);
	while (TRUE)
	{
		get_time(&now);
		if (!check_exit(philo))
			return ;
		if (now - start >= time)
			break ;
		usleep(100);
	}
}