/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:52:24 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/29 16:37:53 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	throw_error(t_phil *phils)
{
	write(2, "Error\n", 6);
	if (phils)
	{
		if (phils[0].inform->state)
			free(phils[0].inform->state);
		free(phils);
	}
	return (0);
}