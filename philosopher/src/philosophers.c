/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:55:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/23 20:59:42 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *inform)
{
	t_inform	*inf;

	inf = (t_inform *)inform;
	printf("%d\n", inf->numOfPhils);
	pthread_exit(0);
}