#include "philo.h"

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
