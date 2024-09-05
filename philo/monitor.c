#include "philo.h"

bool	meal_counter(t_monitor *m, t_philo **philos)
{
	int	i;
	int	num_of_philos;
	int	count_feds;

	i = 0;
	count_feds = 0;
	num_of_philos = get_long(&m->num_of_philos, &m->lock_long_var);
	if (!m->meal_counter)
		return (false);
	else
	{
		while (i < num_of_philos)
		{
			if (get_long(&philos[i]->meal_counter, &m->lock_long_var) >= m->meals)
				count_feds++;
			i++;
		}
		if (count_feds == num_of_philos)
			return (true);
	}
	return (false);
}

bool	check_philo_death(t_philo *philo, t_monitor *m)
{
	long	time_to_die;

	time_to_die = get_long(&m->die, &m->lock_long_var);
	if (time_to_die <= get_ms() - get_long(&philo->last_meal_time, philo->last_meal_lock)
		&& !get_bool(&philo->eating, &m->lock_bools))
			return (true);
	else
		return (false);
}

bool	death_checker(t_philo **philos, t_monitor *m)
{
	int	i;
	int	num_of_philos;

	i = 0;
	num_of_philos = get_long(&m->num_of_philos, &m->lock_long_var);
	while (i < num_of_philos)
	{
		if (check_philo_death(philos[i], m))
			return (true);
		i++;
	}
	return (false);
}

void	*monitor_routine(void *data)
{
	t_monitor *m;

	m = (t_monitor *)data;
	while (!get_bool(&m->end_flag, &m->end_lock))
	{
		if (death_checker(&m->array_of_philos, m) || meal_counter(m, &m->array_of_philos))
			set_bool(&m->end_flag, true, &m->lock_bools);
	}
	return (NULL);
}


void	*death_checker_thread(void *data)
{
	t_philo *p;

	p = (t_philo *)data;
	while (p->monitor->die > get_ms() - p->last_meal_time)
	{
		usleep(1000);
		//end simulation
	}
	if (!(p->eating))
	{
		// p->death_flag = true;
		state_message(DIE, p);
		p->monitor->end_flag = true;
	}

	return (NULL);
}

int	init_monitor(t_monitor *m, char **argv)
{
	safe_mutex_functions(INIT, &m->lock_bools);
	safe_mutex_functions(INIT, &m->lock_long_var);
	safe_mutex_functions(INIT, &m->end_lock);
	safe_mutex_functions(INIT, &m->write_lock);
	safe_mutex_functions(INIT, &m->meal_lock);
	m->meal_counter = false;
	m->end_flag = false;
	m->array_of_philos = (t_philo *)malloc(sizeof(t_philo) * m->num_of_philos);
	if (!m->array_of_philos)
		return (error("couldn't malloc() philos\n"));
	m->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * m->num_of_philos);
	if (!m->forks)
		return (error("couldn't malloc() forks\n"));
	if (argv[5])
		m->meal_counter = true;
	return (1);
}
