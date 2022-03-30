/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:14:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/30 16:33:16 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

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
	long long		start;
}	t_inform;

typedef struct s_phil
{
	t_inform	*inform;
	pthread_t	tid;
	int			me;
	int			left_fork;
	int			right_fork;
	int			numOfEat;
	long long 	now;
}	t_phil;

int		ft_atoi(const char *str);
void	ft_putnbr(int n);
void	ft_putstr(char *s);

void	*dining_phils(void *inform);
int		throw_error(t_phil *phils);
void	print_state(t_phil *philo, int state);

void	eat(t_phil *philo);
// int		leftOf(t_phil *philo);
// int		rightOf(t_phil *philo);
#endif