/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:14:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/23 20:59:21 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

# define SLEEPING 1
# define THINKING 2
# define EATING 3

typedef struct s_inform
{
	int	numOfPhils;
	int	timeToDie;
	int	timeToEat;
	int	timeToSleep;
	int	numOfMustEat;
}	t_inform;

int		ft_atoi(const char *str);
void	*philosophers(void *inform);

#endif