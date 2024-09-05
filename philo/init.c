/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:55:00 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/03 16:01:55 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_mutex(int status, t_mutex_ft func)
{
	if (status == 0)
		return (1);
	else if (status == EINVAL && func == INIT)
		return (error("the value specified by attr is invalid (mutex error)"));
	else if (status == ENOMEM && func == INIT)
		return (error("The process cannot allocate enough memory to create another mutex"));
	else if (status == EBUSY && func == DESTROY)
		return (error("mutex is locked (couldn't destroy)"));
	else if (status == EINVAL)
		return (error("the value specified by mutex is invalid"));
	else if (status == EDEADLK && func == LOCK)
		return (error("A deadlock would occur if the thread blocked waiting for mutex"));
	else if (status == EPERM && func == UNLOCK)
		return (error("the current thrad does not hold a lock on mutex"));
	return (error("mutex"));
}

void	safe_mutex_functions(t_mutex_ft func, pthread_mutex_t *mutex)
{
	if (func == INIT)
		handle_mutex(pthread_mutex_init(mutex, NULL), INIT);
	else if (func == DESTROY)
		handle_mutex(pthread_mutex_destroy(mutex), DESTROY);
	else if (func == LOCK)
		handle_mutex(pthread_mutex_lock(mutex), LOCK);
	else if (func == UNLOCK)
		handle_mutex(pthread_mutex_unlock(mutex), UNLOCK);
	else
		error("wrong mutex code\n");
}

void	philo_info_dump(t_monitor *m, t_philo *philo, int index, pthread_mutex_t *forks)
{
	philo->last_meal_lock = &m->meal_lock;
	philo->end_lock = &m->end_lock;
	philo->write_lock = &m->write_lock;
	philo->lock_bool = &m->lock_bools;
	philo->lock_long = &m->lock_long_var;
	philo->monitor = m;
	philo->index = index + 1;
	philo->position = index;
	philo->meal_counter = 0;	
	if (!(philo->index % 2) && m->num_of_philos > 1)
	{
		philo->first_fork = &forks[(philo->position + 1) % m->num_of_philos];
		philo->second_fork = &forks[(philo->position)];
	}
	else if ((philo->index % 2) && m->num_of_philos > 1)
	{
		philo->first_fork = &forks[(philo->position)];
		philo->second_fork = &forks[(philo->position + 1) % m->num_of_philos];
	}
	else
		philo->first_fork = &forks[0];
}
