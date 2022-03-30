/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:14:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/29 20:27:49 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

# define PICKUP 1
# define SLEEPING 2
# define THINKING 3
# define EATING 4
# define FULL 5
# define DEAD 6

# define TRUE 1

typedef pthread_mutex_t mutex;

typedef struct s_inform
{
	int				numOfPhils;
	int				timeToDie;
	int				timeToEat;
	int				timeToSleep;
	int				numOfMustEat;
	int				*state;
	mutex			main_lock;
	mutex			*fork_mutex;
	mutex			print_lock;
}	t_inform;

typedef struct s_phil
{
	t_inform	*inform;
	pthread_t	tid;
	int			me;
	int			left_fork;
	int			right_fork;
	int			numOfEat;
}	t_phil;

int		ft_atoi(const char *str);
void	ft_putnbr(int n);
void	ft_putstr(char *s);

void	*dining_phils(void *inform);
int		throw_error(t_phil *phils);
int		print_state(t_phil *philo, int state);

int		eat(t_phil *philo);
// int		leftOf(t_phil *philo);
// int		rightOf(t_phil *philo);
#endif