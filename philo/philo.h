/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:17:15 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/12 13:02:36 by zogorzeb         ###   ########.fr       */
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
# include <errno.h>

# define RED "\033[31m"      // Red text
# define GREEN "\033[32m"    // Green text
# define YELLOW "\033[33m"   // Yellow text
# define BLUE "\033[34m"     // Blue text
# define MAGENTA "\033[35m"  // Magenta text
# define CYAN "\033[36m"     // Cyan text
# define WHITE "\033[37m"    // White text
#define RST "\033[0m"     // Resets all text attributes


typedef struct s_monitor t_monitor;

typedef enum	s_state
{
	SLEEP,
	EAT,
	DIE,
	THINK,
	F_FORK,
	S_FORK
}	t_state;

typedef enum	s_mutex_ft
{
	LOCK,
	UNLOCK,
	DESTROY,
	INIT
}	t_mutex_ft;

typedef struct s_philo
{
	pthread_t			philo_thread;
	int					index;
	pthread_mutex_t		*last_meal_lock;
	long				last_meal_time; // will be accessed by monitor! get a mutex 🔐
	long				meal_counter; // will be accessed by monitor 🔐
	t_monitor			*monitor;
	int					position;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*end_lock;
	pthread_mutex_t		*lock_long;
	pthread_mutex_t 	*lock_bool;
	bool				*end_flag;
	bool				eating;
	bool				dead;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		death_checker;
	t_philo			*array_of_philos;
	// first argument -> number of philos and at the same time number of forks
	long			num_of_philos;
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
	pthread_mutex_t lock_bools;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_long_var;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	meal_lock;
	bool			meal_counter;
	bool			end_flag;
}	t_monitor;

void	philo_info_dump(t_monitor *m, t_philo *philo, int index, pthread_mutex_t *forks);
void	fork_info_dump(pthread_mutex_t *fork);
int		check_args(char **argv, t_monitor *m, int argc);
int		ft_isdigit(int c);
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
int		error(char *message);
void	timestamp(long beginning, long *timestamp);
long	get_ms();
void	single_philo_routine(t_monitor *m, t_philo *p);
void	state_message(t_state state, t_philo *p);
int		init_philosophers(t_monitor *monitor, t_philo *philo);
void	philo_eat(t_monitor *m, t_philo *p);
void	*routine(void *data);
// MUTEX
int		handle_mutex(int status, t_mutex_ft func);
void	safe_mutex_functions(t_mutex_ft func, pthread_mutex_t *mutex);
long	get_long(long *var, pthread_mutex_t *lock);
void	set_long(long *src, long dest, pthread_mutex_t *lock);
bool	get_bool(bool *var, pthread_mutex_t *lock);
void	set_bool(bool *src, bool dest, pthread_mutex_t *lock);
// MONITOR 
int		init_monitor(t_monitor *m, char **argv);
// void	*death_checker_thread(void *data);
void	*monitor_routine(void *data);
bool	death_checker(t_philo *philos, t_monitor *m);

#endif