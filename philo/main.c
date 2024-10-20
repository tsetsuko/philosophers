/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:14:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/10/20 20:06:02 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_monitor *m, t_philo *array)
{
	int	i;

	i = 0;
	while (i < m->num_of_philos)
	{
		safe_mutex_functions(DESTROY, &m->forks[i]);
		i++;
	}
	free(array);
	safe_mutex_functions(DESTROY, &m->end_lock);
	safe_mutex_functions(DESTROY, &m->lock_bools);
	safe_mutex_functions(DESTROY, &m->lock_long_var);
	safe_mutex_functions(DESTROY, &m->meal_lock);
	safe_mutex_functions(DESTROY, &m->write_lock);
	free(m->forks);
	free(m);
}

int	multiple_philos_sim(long num_of_p, t_monitor *m, t_philo *p)
{
	long	i;

	i = 0;
	while (i < num_of_p)
	{
		if (pthread_create(&(p[i].philo_thread), NULL, &routine, &p[i]) != 0)
			error("thread not created");
		set_long(&(p[i].last_meal_time), get_ms(), p[i].last_meal_lock);
		i++;
	}
	if (num_of_p > 1)
		pthread_create(&m->death_checker, NULL, &monitor_routine, m);
	i = 0;
	while (i < num_of_p)
	{
		pthread_join(p[i].philo_thread, NULL);
		i++;
	}
	if (num_of_p > 1)
		pthread_join(m->death_checker, NULL);
	return (1);
}

int	start_simulation(t_monitor *m, t_philo *p)
{
	long	num_of_p;

	set_long(&m->beginning, get_ms(), &m->lock_long_var);
	num_of_p = get_long(&m->num_of_philos, &m->lock_long_var);
	if (num_of_p == 1)
		single_philo_routine(m, p);
	else
		multiple_philos_sim(num_of_p, m, p);
	return (1);
}

int	init_philosophers(t_monitor *monitor, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < monitor->num_of_philos)
	{
		philo_info_dump(monitor, &philo[i], i, monitor->forks);
		safe_mutex_functions(INIT, &monitor->forks[i]);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)malloc(sizeof(t_monitor) * 1);
	if (argc == 5 || argc == 6)
	{
		if (!check_args(argv, monitor, argc))
			return (1);
		if (!init_monitor(monitor, argv))
			return (2);
		if (!init_philosophers(monitor, monitor->array_of_philos))
			return (3);
		if (!start_simulation(monitor, monitor->array_of_philos))
			return (4);
		clean_up(monitor, monitor->array_of_philos);
	}
	return (0);
}
