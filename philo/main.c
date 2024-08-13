/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:14:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/12 14:02:11 by zogorzeb         ###   ########.fr       */
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
	m->beginning = get_ms();
	printf(MAGENTA"start sim beginning: %ld\n"RST, m->beginning);
	if (m->num_of_philos == 1)
		single_philo_routine(m, p);
	else
	{	
		while (i < m->num_of_philos)
		{
			printf("entered create thread loop\n");
			if (pthread_create(&(p[i].philo_thread), NULL, &routine, &p[i]) != 0)
			{
				error("thread gone bad");
				// return (0);	
			}
			else
				printf("thread create ok\n");
			i++;
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
		fork_info_dump(&monitor->forks[i]);
		i++;
	}
	return (1);
}

static int	init_monitor(t_monitor *m, char **argv)
{
	m->meal_counter = false;
	m->end_flag = false;
	m->array_of_philos = (t_philo *)malloc(sizeof(t_philo) * m->num_of_philos);
	if (!m->array_of_philos)
	{
		error("couldn't malloc() philos\n");
		return (0);
	}
	m->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * m->num_of_philos);
	if (!m->forks)
	{
		error("couldn't malloc() forks\n");
		return (0);
	}
	if (argv[5])
		m->meal_counter = true;
	return (1);
}
int main(int argc, char **argv)
{
	t_monitor monitor;

	if (argc == 5 || argc == 6)
	{
		// 🧾 🧾 check if the arguments are all non-alpha
		if (!check_args(argv, &monitor))
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
