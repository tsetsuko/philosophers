/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:14:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/12 13:32:31 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

// bool	end_simulation()
// {
	// if death_flag

// }

int	start_simulation(t_monitor *m, t_philo *p)
{
	int i;
	long	num_of_p;

	i = 0;
	set_long(&m->beginning, get_ms(), &m->lock_long_var);
	num_of_p = get_long(&m->num_of_philos, &m->lock_long_var);
	// printf(MAGENTA"start sim beginning: %ld\n"RST, m->beginning);
	if (num_of_p == 1)
		single_philo_routine(m, p);
	else
	{	
		while (i < num_of_p)
		{
			if (pthread_create(&(p[i].philo_thread), NULL, &routine, &p[i]) != 0)
				error("thread not created");
			i++;
		}
	}
	// start monitor thread
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
	/*
	start of simulation timestamp?
	int i = 0;

	timestamp(m->start_of_sim);

	if (num_of_philos == 1)
		single_philo_routine();

	while (i < m->num_of_philos)
	{
		routine(m, philo[i]);
		i++;
	}
	start every philo thread
	and monitor thread
	*/

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


int main(int argc, char **argv)
{
	t_monitor *monitor;

	monitor = (t_monitor *)malloc(sizeof(t_monitor) * 1);
	if (argc == 5 || argc == 6)
	{
		// 🧾 🧾 check if the arguments are all non-alpha
		if (!check_args(argv, monitor, argc))
			return (1);
		if (!init_monitor(monitor, argv))
			return (2);
		if (!init_philosophers(monitor, monitor->array_of_philos))
			return (3);
		if (!start_simulation(monitor, monitor->array_of_philos))
			return (4);
		// clean up -> destroy locks and stack memory
	}
	return (0);

}
