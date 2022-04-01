/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:14:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/01 21:45:44 by jinyoo           ###   ########.fr       */
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
# define FINISH 5
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
	int				numOfFinishingEat;
	mutex			main_lock;
	mutex			*fork_mutex;
	mutex			print_lock;
	long long		start;
	int				isDie;
	int				isFin;
}	t_inform;

typedef struct s_phil
{
	t_inform	*inform;
	pthread_t	dining_tid;
	pthread_t	monitoring_tid;
	int			me;
	int			left_fork;
	int			right_fork;
	int			numOfEat;
	long long 	time;
}	t_phil;

int		ft_atoi(const char *str);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
void	ft_putendl(char *s);

void	*dining_phils(void *inform);
void	*monitoring(void *phil);
int		throw_error(t_phil *phils);
void	print_state(t_phil *philo, int state);

void	p_eat(t_phil *philo);
void	p_sleep(t_phil *philo);
void	p_think(t_phil *philo);

void	get_time(long long *val);
void	time_travel(t_phil *philo, long long start, long long time);
int		check_exit(t_phil *philo);
// int		leftOf(t_phil *philo);
// int		rightOf(t_phil *philo);
#endif