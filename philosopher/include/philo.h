/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:14:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/04/04 18:16:43 by jinyoo           ###   ########.fr       */
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

typedef pthread_mutex_t	t_mutex;

typedef struct s_inform
{
	int				num_phils;
	int				tim_die;
	int				tim_eat;
	int				time_sleep;
	int				num_must_eat;
	int				num_fin_eat;
	int				*state;
	t_mutex			*fork_mutex;
	t_mutex			print_lock;
	long long		*time;
	long long		start;
	int				die;
	int				fin;
	pthread_t		monitoring_tid;
}	t_inform;

typedef struct s_phil
{
	t_inform	*inform;
	pthread_t	dining_tid;
	int			me;
	int			left_fork;
	int			right_fork;
	int			num_eat;
}	t_phil;

int		ft_atoi(const char *str);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
void	ft_putendl(char *s);

void	*dining_phils(void *inform);
void	*monitoring(void *phil);
void	print_state(t_phil *philo, int state);

int		phils_guide(t_phil *philo);
void	p_eat(t_phil *philo);
void	p_sleep(t_phil *philo);
void	p_think(t_phil *philo);

void	get_time(long long *val);
void	time_travel(long long start, long long time);

int		throw_error(t_phil *phils);
int		ft_exit(t_phil *phils);

#endif