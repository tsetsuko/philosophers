/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:17:15 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/09 23:14:16 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>

# define RED "\033[31m"      // Red text
# define GREEN "\033[32m"    // Green text
# define YELLOW "\033[33m"   // Yellow text
# define BLUE "\033[34m"     // Blue text
# define MAGENTA "\033[35m"  // Magenta text
# define CYAN "\033[36m"     // Cyan text
# define WHITE "\033[37m"    // White text
#define RST "\033[0m"     // Resets all text attributes


typedef struct s_monitor t_monitor;
typedef struct	s_forks	t_forks;

typedef enum	s_state
{
	SLEEP,
	EAT,
	DIE,
	THINK,
	F_FORK,
	S_FORK
}	t_state;

typedef struct s_philo
{
	pthread_t	philo_thread;
	int			index;
	long		last_meal_time;
	int			meal_counter;
	t_monitor	*monitor;
	t_forks		**forks;
	int			position;
	t_forks		*first_fork;
	t_forks		*second_fork;
	bool		death_flag;
}	t_philo;

typedef struct s_monitor
{
	// first argument -> number of philos and at the same time number of forks
	int				num_of_philos;
	// second argument -> time a philo can spend without eating,
	// after that time, philo dies
	long			die;
	// third arg -> time philo takes to eat
	long			time_of_eating;
	// forth arg -> time of sleeping
	long			sleep;
	// fifth arg -> [optional] how many times a philo has to eat
	int				meals;
	long			beginning;
	t_philo			*array_of_philos;
	pthread_mutex_t lock_end;
	bool			meal_counter;
	bool			end_flag;
}	t_monitor;

typedef struct	s_forks
{
	// mutex and id
	pthread_mutex_t lock;
	int				index;
}	t_forks;

void	philo_info_dump(t_monitor *m, t_philo *philo, int index, t_forks **forks);
void	fork_info_dump(t_forks *fork, int i);
int		check_args(char **argv, t_monitor *m);
int		ft_isdigit(int c);
long	ft_atol(const char *str);
void	error(char *message);
void	timestamp(long beginning, long *timestamp);
long	get_ms();
void	single_philo_routine(t_monitor *m, t_philo *p);
void	state_message(long beginning, t_state state, int index);
int		init_philosophers(t_monitor *monitor, t_philo *philo);
void	philo_eat(t_monitor *m, t_philo *p);

#endif