/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:21 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/12 14:14:21 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// this function will provide sleep for the philo but it will also check
// if the simulation hasn't stopped in the meanwhile
void	philo_sleep(t_monitor *m, long time)
{
	// long	wake_up;
	long	now;

	now = get_ms();
	// wake_up = now + time;
	while (time > get_ms() - now)
	{
		if (m->end_flag)
		{
			printf("end\n");
			break ;
		}
		usleep(100);
	}
}

int	death_checker(t_monitor *m, t_philo *philo, long beginning)
{
	long	now_time;

	timestamp(beginning, &now_time);
	if (m->die <= now_time)
	{
		philo->death_flag = true;
		state_message(m->beginning, DIE, philo);
		m->end_flag = true;
		//end simulation
	}
	return (1);
}

void	single_philo_routine(t_monitor *m, t_philo *p)
{
	pthread_mutex_lock(&p->forks[p->position]);
	state_message(m->beginning, F_FORK, p);
	philo_sleep(m, m->die);
	death_checker(m, p, m->beginning);
	pthread_mutex_unlock(&p->forks[p->position]);
}

void	state_message(long beginning, t_state state, t_philo *p)
{
	long	ms;

	// create a write lock

	pthread_mutex_lock(&p->write_message);
	timestamp(beginning, &ms);
	if (state == SLEEP)
		printf("%ldms %d is sleeping\n", ms, p->index);
	else if (state == EAT)
		printf("%ldms %d is eating\n", ms, p->index);
	else if (state == DIE)
		printf("%ldms %d died\n", ms, p->index);
	else if (state == S_FORK)
		printf("%ldms %d has taken second fork\n", ms, p->index);
	else if (state == F_FORK)
		printf("%ldms %d has taken first fork\n", ms, p->index);
	else
		error("wrong enum for the state message\n");
	pthread_mutex_unlock(&p->write_message);

}

void	*routine(void *data)
{
	int			i;
	t_philo 	*p;
	// pthread_t	death_checker;

	i = 0;
	p = (t_philo *)data;
	// pthread_mutex_lock(&p->last_meal_lock);
	p->last_meal_time = p->monitor->beginning;
	// pthread_mutex_unlock(&p->last_meal_lock);
	printf("beginning [%d]: %ld\n", p->index, p->monitor->beginning);
	printf("hey it's %d\n", p->index);
	// if (pthread_create(&death_checker, NULL, &death_checker_thread, p) == 0)
	// 	printf("supervisor goes\n");
	while (p->monitor->end_flag == false)
	{
		printf("entered routine loop\n");
		philo_eat(p->monitor, p);
	// sleep
		state_message(p->monitor->beginning, SLEEP, p);
		philo_sleep(p->monitor, p->monitor->sleep);
	// think
		state_message(p->monitor->beginning, THINK, p);
	// death_checker
	//		again!
	// if time_to_die passed --> die flag --> monitor ends the simulation}
	}
	return (NULL);
	
}
