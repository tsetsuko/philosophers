#include "philo.h"



// we also need single philo routine

//state message

void	state_message(t_state state, int index)
{
	long	ms;

	// ms = 
	// create a write lock
	if (state == SLEEP)
		printf("%ld ms %d is sleeping\n", ms, index);
	else if (state == EAT)
		printf("%ld ms %d is eating\n", ms, index);
	else if (state == DIE)
		printf("%ld ms %d died\n", ms, index);
	else if (state == S_FORK)
		printf("%ld ms %d has taken second fork\n", ms, index);
	else if (state == F_FORK)
		printf("%ld ms %d has taken first fork\n", ms, index);
	else
		error("wrong enum for the state message\n");
}

int	routine(t_monitor *m, t_philo *p)
{
	int	i;

	i = 0;
	while (!(end_simulation()))
	{
		if (!(p->index % 2))
		{
			p->first_fork = p->forks[p->position + 1];
			pthread_mutex_lock(p->forks[(p->position + 1) % m->num_of_philos]);
			state_message(F_FORK, p->index);
			p->second_fork = p->forks[p->position];
			pthread_mutex_lock(p->forks[(p->position)]);
			state_message(S_FORK, p->index);
		}
		else
		{
			p->first_fork = p->forks[p->position];
			pthread_mutex_lock(p->forks[(p->position)]);
			state_message(F_FORK, p->index);
			p->second_fork = p->forks[(p->position + 1) % m->num_of_philos];
			pthread_mutex_lock(p->forks[(p->position + 1) % m->num_of_philos]);
			state_message(S_FORK, p->index);
		}
	// EAT - lock mutex
		if (p->first_fork && p->second_fork)
		{
		// update timestamp
			state_message(EAT, p->index);
			usleep(m->time_of_eating * 1000);
			if (m->meal_counter == true)
				p->meal_counter++;
			pthread_mutex_unlock(p->forks[(p->position + 1) % m->num_of_philos]);
			pthread_mutex_unlock(p->forks[(p->position)]);
		}
	// sleep
		state_message(SLEEP, p->index);
		usleep(m->sleep * 1000);
	// think

	//		again!
	// if time_to_die passed --> die flag --> monitor ends the simulation}
	}
}
