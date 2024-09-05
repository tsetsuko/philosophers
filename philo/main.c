/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:14:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/03 16:07:28 by zogorzeb         ###   ########.fr       */
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

	i = 0;
	set_long(&m->beginning, get_ms(), &m->lock_long_var);
	printf(MAGENTA"start sim beginning: %ld\n"RST, m->beginning);
	if (get_long(&m->num_of_philos, &m->lock_long_var) == 1)
		single_philo_routine(m, p);
	else
	{	
		while (i < m->num_of_philos)
		// while (i < get_long(&m->num_of_philos, &m->lock_long_var))
		{
			// printf("entered create thread loop\n");
			if (pthread_create(&(p[i].philo_thread), NULL, &routine, &p[i]) != 0)
			{
				error("thread not created");
				return (0);
			}
			i++;
			if (pthread_create(&(p[i].philo_thread), NULL, &routine, &p[i]) != 0)
			{
				error("thread not created");
				return (0);
			}
			// i++;
		}
	}
	i = 0;
	// while (i < m->num_of_philos)
	// {
	// 	pthread_join(p[i]->philo_thread, NULL);
	// 	i++;
	// }
	// start monitor thread
	// if (m->num_of_philos > 1)
	//		
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
	t_monitor monitor;

	if (argc == 5 || argc == 6)
	{
		// 🧾 🧾 check if the arguments are all non-alpha
		if (!check_args(argv, &monitor, argc))
			return (1);
		if (!init_monitor(&monitor, argv))
			return (2);
		if (!init_philosophers(&monitor, monitor.array_of_philos))
			return (3);
		if (!start_simulation(&monitor, monitor.array_of_philos))
			return (4);
		// clean up -> destroy locks and stack memory
	}
	return (0);

}
