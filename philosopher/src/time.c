/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:21:30 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/30 16:28:07 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_saving(long long *val)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	*val = (long long)(tv.tv_sec * MILLI + tv.tv_usec / MILLI);
}